/**
 * @author Jaroslav Fikar
 * 
*/


#include "CBoard.h"

CBoard::~CBoard()
{
    for (size_t i = 0; i < this->m_BoardSize.m_X; i++)
    {
        for (size_t j = 0; j < this->m_BoardSize.m_Y; j++)
        { delete this->m_Map[i][j]; }
    }
    this->m_Map.clear();

    for (size_t i = 0; i < this->m_Players.size(); i++)
    { delete this->m_Players[i]; }
    this->m_Players.clear();

    for (size_t i = 0; i < this->m_Enemies.size(); i++)
    { delete this->m_Enemies[i]; }
    this->m_Enemies.clear();

    for (auto i = this->m_Bombs.begin(); i != this->m_Bombs.end(); i++)
    { delete i->second; }
    this->m_Bombs.clear();

    for (auto i = this->m_Fires.begin(); i != this->m_Fires.end(); i++)
    { delete i->second; }
    this->m_Fires.clear();

    for (auto i = this->m_Collectibles.begin(); i != this->m_Collectibles.end(); i++)
    { delete i->second; }
    this->m_Collectibles.clear();
}

/*====================================================================================================================*/
bool CBoard::IsPassable(CCoord<unsigned int> coord, const CPlayer *player)
{
    // Array index check.
    if (coord.m_X < 0 || coord.m_X >= CBoard::m_BoardSize.m_X ||
        coord.m_Y < 0 || coord.m_Y >= CBoard::m_BoardSize.m_Y)
    { throw std::out_of_range(MESSAGE_INDEX_OUT_OF_BOUND); }

    CWall *wall = this->m_Map[coord.m_X][coord.m_Y];

    if (wall && wall->IsAlive() && (!wall->IsDestructible() || !player->GetWallPass()))
    { return false; }

    // Search for bombs in location.
    auto bomb = this->m_Bombs.find(coord);
    if (bomb != this->m_Bombs.end() && bomb->second && !player->GetBombPass() && player->IsColiding(bomb->second))
    {
        // Player is not owner or the bomb is not passable for owner
        if (bomb->second->GetOwner() != player || !bomb->second->IsPassableForOwner())
        { return false; }
    }

    return true;
}

/*====================================================================================================================*/
bool CBoard::PlaceBomb(CPlayer *player)
{
    CCoord<unsigned int> location = player->GetLocationCell();

    // We do not want to plant bombs on a wall.
    if (this->m_Map[location.m_X][location.m_Y] != nullptr)
    { return false; }

    int delay = 2000;
    if (player->GetRemoteExplosion())
    { delay = 100; }
    // If this location is free.
    if (this->m_Bombs.find(location) == this->m_Bombs.end() && this->m_Fires.find(location) == this->m_Fires.end())
    {
        CBomb *bomb = new CBomb(this->m_BombObjectTexturePack, this->m_BombObjectTexturePack->GetTextureSize(),
                                location.ToDouble(), player, delay, player->GetRemoteExplosion());

        this->m_Bombs.insert({location.ToUnsignedInt(), bomb});
        return true;
    }

    return false;
}

/*====================================================================================================================*/
void CBoard::DetonateBombs(const CPlayer *player)
{
    for (auto i = this->m_Bombs.begin(); i != this->m_Bombs.end(); i++)
    {
        if (i->second->GetOwner() == player)
        { i->second->Detonate(this); }
    }
}

/*====================================================================================================================*/
void CBoard::CreateExplosion(CBomb *bomb)
{
    if (bomb)
    {
        CPlayer *owner = bomb->GetOwner();

        if (owner)
        {
            unsigned int explosionRadius = owner->GetExplosionRadius();

            // Explosion in all directions.
            CCoord<int> directions[4] = {CCoord<int>(0, 1), CCoord<int>(0, -1), CCoord<int>(1, 0), CCoord<int>(-1, 0)};
            for (int i = 0; i < 4; i++)
            { this->CreateExplosionWave(bomb, directions[i], explosionRadius); }
        }

        CCoord<unsigned int> location = bomb->GetLocation().ToUnsignedInt();
        auto bombToRemove = this->m_Bombs.find(location);
        if (bombToRemove != this->m_Bombs.end())
        {
            delete bombToRemove->second;
            bombToRemove->second = nullptr;
            this->m_Bombs.erase(bombToRemove);
        }
            // Error message when the bomb is not found - this should never happen
        else
        { std::cerr << "Bomb " << location << " not found " << std::endl; }
    }
}

/*====================================================================================================================*/
void CBoard::CreateExplosionWave(CBomb *bomb, CCoord<int> direction, unsigned int explosionRadius)
{
    for (unsigned int i = 0; i <= explosionRadius; i++)
    {
        CCoord<unsigned int> locationToExplode = (bomb->GetLocation() + (i * direction).ToDouble()).ToUnsignedInt();

        if (locationToExplode.m_X < 0 || locationToExplode.m_X >= CBoard::m_BoardSize.m_X ||
            locationToExplode.m_Y < 0 || locationToExplode.m_Y >= CBoard::m_BoardSize.m_Y)
        { throw std::out_of_range(MESSAGE_INDEX_OUT_OF_BOUND); }

        // Target exists and its not destructible.
        CWall *target = this->m_Map[locationToExplode.m_X][locationToExplode.m_Y];
        if ((target && !target->IsDestructible()))
        { break; /* Leave for loop - The wave was stopped by this indestructible wall.*/        }

        bool wallDestroyed = false;

        if (target)
        {
            if (target->TryDestroy(i))
            {
                delete target;
                this->m_Map[locationToExplode.m_X][locationToExplode.m_Y] = nullptr;
                wallDestroyed = true;
            } else
            { break; /* Leave for loop - The wave was stopped by this wall.*/            }
        }

        // Find collectible in location to explode.
        auto foundCollectible = this->m_Collectibles.find(
                locationToExplode.ToUnsignedInt());
        if (foundCollectible != this->m_Collectibles.end())
        { break; /* leave for loop - We dont want burning collectibles*/        }

        // Find bomb in location to explode.
        auto foundBomb = this->m_Bombs.find(locationToExplode.ToUnsignedInt());
        if (foundBomb != this->m_Bombs.end() && foundBomb->second != bomb)
        { break; /* leave for loop - We dont want burning bombs.*/        }


        // Destroy potencialy existing fire is this location.
        auto foundFire = this->m_Fires.find(locationToExplode.ToUnsignedInt());
        if (foundFire != this->m_Fires.end())
        {
            // Remove old fire.
            delete (foundFire->second);
            foundFire->second = nullptr;
            this->m_Fires.erase(foundFire);
        }

        // Create new fire.
        CFire *fire = new CFire(this->m_FireObjectTexturePack, this->m_FireObjectTexturePack->GetTextureSize(),
                                locationToExplode.ToDouble());
        this->m_Fires.insert({locationToExplode.ToUnsignedInt(), fire});

        if (wallDestroyed)
        { break; /* Explosion was stopped by destroyed wall. */ }
    }
}

/*====================================================================================================================*/
void CBoard::DestroyExplosion(CFire *fire)
{
    CCoord<> fireLocation = fire->GetLocation();
    auto fireToRemove = this->m_Fires.find(fireLocation.ToUnsignedInt());
    if (fireToRemove != this->m_Fires.end())
    {
        delete (fireToRemove->second);
        fireToRemove->second = nullptr;
        this->m_Fires.erase(fireToRemove);
    }
        // Error message when the fire is not found - this should never happen
    else
    { std::cerr << "Fire " << fireLocation << " not found " << std::endl; }
}

/*====================================================================================================================*/
void CBoard::DestroyCollectible(CCollectible *collectible)
{
    CCoord<> collectibleLocation = collectible->GetLocation();
    auto collectibleToRemove = this->m_Collectibles.find(collectibleLocation.ToUnsignedInt());
    if (collectibleToRemove != this->m_Collectibles.end())
    {
        delete (collectibleToRemove->second);
        collectibleToRemove->second = nullptr;
        this->m_Collectibles.erase(collectibleToRemove);
    }
        // Error message when the collectible is not found - this should never happen
    else
    { std::cerr << "Collectible " << collectibleLocation << " not found " << std::endl; }
}

/*====================================================================================================================*/
void CBoard::Draw(CSDLInterface *interface, CCoord<> offset)
{
    // draw map
    for (size_t i = 0; i < this->m_BoardSize.m_X; i++)
    {
        for (size_t j = 0; j < this->m_BoardSize.m_Y; j++)
        {
            if (this->m_Map[i][j])
            { this->m_Map[i][j]->Draw(interface, this->m_CellSize, CCoord<unsigned int>(i, j).ToDouble(), offset); }
            else if (this->m_GroundObject)
            { this->m_GroundObject->Draw(interface, this->m_CellSize, CCoord<unsigned int>(i, j).ToDouble(), offset); }
        }
    }

    // Draw boosts is visible
    for (auto i = this->m_Collectibles.begin(); i != this->m_Collectibles.end(); i++)
    {
        // std::cout << i->second->GetLocation() << std::endl;
        if (i->second && i->second->IsVisible())
        { i->second->Draw(interface, this->m_CellSize, i->first.ToDouble(), offset); }
            /*==DEBUG==*/
        else if (this->m_Settings->GetDebugMode())
        {
            CCoord<int> location = i->second->GetLocation().ToInt() + offset.ToInt();
            SDL_Rect rect{static_cast<int>(location.m_X * (m_CellSize)),
                          static_cast<int>(location.m_Y * (m_CellSize)),
                          static_cast<int>(m_CellSize), static_cast<int>(m_CellSize)};
            interface->RenderRectangle(&rect);
        }
    }

    // draw bombs
    for (auto i = this->m_Bombs.begin(); i != this->m_Bombs.end(); i++)
    {
        if (i->second)
        { i->second->Draw(interface, this->m_CellSize, i->first.ToDouble(), offset); }
    }

    // draw fires
    for (auto i = this->m_Fires.begin(); i != this->m_Fires.end(); i++)
    {
        if (i->second)
        { i->second->Draw(interface, this->m_CellSize, i->first.ToDouble(), offset); }
    }

    // Draw enemies
    for (size_t i = 0; i < this->m_Enemies.size(); i++)
    {
        if (this->m_Enemies[i])
        { this->m_Enemies[i]->Draw(interface, this->m_CellSize, this->m_Enemies[i]->GetLocation(), offset); }
    }

    // TODO změnit pořadí renderu tak, aby nejdříve byly renderovány objekty, které jsou vespod.
    // draw players
    for (size_t i = 0; i < this->m_Players.size(); i++)
    {
        if (this->m_Players[i])
        { this->m_Players[i]->Draw(interface, this->m_CellSize, this->m_Players[i]->GetLocation(), offset); }
    }
}

/*====================================================================================================================*/
void CBoard::Update(int deltaTime)
{
    // Update map (Walls)
    for (size_t i = 0; i < this->m_BoardSize.m_X; i++)
    {
        for (size_t j = 0; j < this->m_BoardSize.m_Y; j++)
        {
            // Update if object is alive
            if (this->m_Map[i][j]/* && this->m_Map[i][j]->IsAlive()*/)
            { this->m_Map[i][j]->Update(this, deltaTime); }
        }
    }

    // Update players
    for (size_t i = 0; i < this->m_Players.size(); i++)
    { this->m_Players[i]->Update(this, deltaTime); }

    // Update enemies
    for (size_t i = 0; i < this->m_Enemies.size(); i++)
    {
        // Polymorphic call
        this->m_Enemies[i]->Update(this, deltaTime);
    }

    // Update collectibles
    for (auto i = this->m_Collectibles.begin(); i != this->m_Collectibles.end();/* i++*/)
    {
        // Save iterator to next object because current bomb could be removed in Update().
        auto item = i++;
        if (item->second)
        { item->second->Update(this, deltaTime); }
        else
        {
            // Remove null item
            this->m_Collectibles.erase(item);
        }
    }

    // Update bombs
    for (auto i = this->m_Bombs.begin(); i != this->m_Bombs.end();/* i++*/)
    {
        // Save iterator to next object because current bomb could be removed in Update().
        auto item = i++;
        if (item->second)
        { item->second->Update(this, deltaTime); }
        else
        {
            // Remove null item
            this->m_Bombs.erase(item);
        }
    }

    // Update fires
    for (auto i = this->m_Fires.begin(); i != this->m_Fires.end();)
    {
        // Save iterator to next object because current fire could be removed in Update().
        auto item = i++;
        if (item->second)
        { item->second->Update(this, deltaTime); }
        else
        {
            // Remove null item
            this->m_Fires.erase(item);
        }
    }
}

/*====================================================================================================================*/
void CBoard::UpdatePhysicEvents()
{
    for (auto player = this->m_Players.begin(); player != this->m_Players.end(); player++)
    {
        if ((*(player)) && (*(player))->IsAlive())
        {
            // Fire collision
            for (auto fire = this->m_Fires.begin(); fire != this->m_Fires.end(); fire++)
            {
                // Kill player if player is colliding fire and do he does not have fire imunity.
                if (fire->second && !(*(player))->GetFireImunity() && (*(player))->IsColiding(fire->second))
                {
                    (*(player))->Kill();
                    return; // player is dead and he cant pickup collectible items.
                }
            }

            // Collectible collision
            for (auto collectible = this->m_Collectibles.begin();
                 collectible != this->m_Collectibles.end(); collectible++)
            {
                if (collectible->second && collectible->second->IsVisible() &&
                    (*(player))->IsColiding(collectible->second))
                {
                    // Polymorphic call
                    collectible->second->Apply((*(player))); // Apply item
                }
            }
        }
    }
}

/*====================================================================================================================*/
void CBoard::ClearBoard(bool clearLevelObjects)
{
    // Delete walls
    for (size_t i = 0; i < this->m_BoardSize.m_X; i++)
    {
        for (size_t j = 0; j < this->m_BoardSize.m_Y; j++)
        {
            // Delete wall if is destructible
            if (this->m_Map[i][j] && this->m_Map[i][j]->IsDestructible())
            {
                delete (this->m_Map[i][j]);
                this->m_Map[i][j] = nullptr;
            }
        }
    }

    // Delete level objects - New level is going to ge loaded.
    if (clearLevelObjects)
    {
        for (auto i = this->m_Collectibles.begin(); i != this->m_Collectibles.end(); i++)
        { delete (i->second); }
        this->m_Collectibles.clear();

        for (auto i = this->m_Enemies.begin(); i != this->m_Enemies.end(); i++)
        { delete (*i); }
        this->m_Enemies.clear();
    }
    else
    {
        for (auto i = this->m_Collectibles.begin(); i != this->m_Collectibles.end(); i++)
        { i->second->MakeInvisible(); }
    }

    // Delete bombs
    for (auto i = this->m_Bombs.begin(); i != this->m_Bombs.end(); i++)
    {
        delete (i->second);
        i->second = nullptr;
    }
    this->m_Bombs.clear();

    // Delete fires
    for (auto i = this->m_Fires.begin(); i != this->m_Fires.end(); i++)
    {
        delete (i->second);
        i->second = nullptr;
    }
    this->m_Fires.clear();

    // Rerun players locations
    for (size_t i = 0; i < this->m_Players.size(); i++)
    { this->m_Players[i]->Reset(); }
}

/*====================================================================================================================*/
bool CBoard::PositionFree(CCoord<unsigned int> coord)
{
    if (coord.m_X < 0 || coord.m_X >= CBoard::m_BoardSize.m_X ||
        coord.m_Y < 0 || coord.m_Y >= CBoard::m_BoardSize.m_Y)
    { throw std::out_of_range(MESSAGE_INDEX_OUT_OF_BOUND); }

    // Check walls
    if (this->m_Map[coord.m_X][coord.m_Y] != nullptr ||
        this->m_Bombs.find(coord) != this->m_Bombs.end() ||
        this->m_Fires.find(coord) != this->m_Fires.end() ||
        this->m_Collectibles.find(coord) != this->m_Collectibles.end())
    { return false; }

    for (size_t i = 0; i < this->m_Players.size(); i++)
    {
        if (m_Players[i]->GetLocation().AlmostEqual(coord.ToDouble()))
        { return false; }
    }

    for (size_t i = 0; i < this->m_Enemies.size(); i++)
    {
        if (m_Enemies[i]->GetLocation().AlmostEqual(coord.ToDouble()))
        { return false; }
    }

    return true;
}

/*====================================================================================================================*/
bool CBoard::PlayersAreaFree(CCoord<unsigned int> coord)
{
    // Create direction vectors.
    CCoord<int> directions[4] = {CCoord<int>(0, 1), CCoord<int>(0, -1), CCoord<int>(1, 0), CCoord<int>(-1, 0)};

    for (std::vector<CPlayer *>::size_type i = 0; i < this->m_Players.size(); i++)
    {
        for (unsigned int j = 0; j < 4; j++)
        {
            if (!this->PlayerDirectionFree(coord, this->m_Players[i], directions[j]))
            { return false; }
        }
    }

    return true;
}

/*====================================================================================================================*/
bool CBoard::PlayerDirectionFree(CCoord<unsigned int> location, CPlayer *player, CCoord<int> direction)
{
    for (unsigned int i = 0; i <= player->GetExplosionRadius(); i++)
    {
        CCoord<> curLocation = (player->GetLocation() + (direction * i).ToDouble());

        if (curLocation == location.ToDouble())
        { return false; }
    }

    return true;
}













