/**
 * @author Jaroslav Fikar
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

    for (auto i = this->m_Collectibles.begin(); i != this->m_Collectibles.end(); i++)
    { delete i->second; }
    this->m_Collectibles.clear();
}

/*====================================================================================================================*/
bool CBoard::IsPassable(CCoord<unsigned int> coord, const CMovable *movable)
{
    CBlock *block = this->GetMapItem(coord);

    if (block && block->IsAlive() && !block->IsPassable(coord, *movable))
    { return false; }

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

    CBomb *bomb = new CBomb(this->m_BombObjectTexturePack, this->m_BombObjectTexturePack->GetTextureSize(), player,
                            delay, player->GetRemoteExplosion());
    this->m_Map[location.m_X][location.m_Y] = bomb;

    return true;
}

/*====================================================================================================================*/
void CBoard::CreateExplosion(CBomb *bomb, CCoord<unsigned int> bombLocation)
{
    if (bomb)
    {
        CPlayer *owner = bomb->GetOwner();

        // Remove the bomb.
        this->SetMapItem(nullptr, bombLocation);

        if (owner)
        {
            unsigned int explosionRadius = owner->GetExplosionRadius();

            // Explosion in all directions.
            CCoord<int> directions[4] = {CCoord<int>(0, 1), CCoord<int>(0, -1), CCoord<int>(1, 0), CCoord<int>(-1, 0)};
            for (int i = 0; i < 4; i++)
            { this->CreateExplosionWave(bombLocation, directions[i], explosionRadius); }
        }

        // Remove from the list of requests.
        this->m_BombsToExplode.erase(bomb);
    }
}

/*====================================================================================================================*/
void CBoard::CreateExplosionWave(CCoord<unsigned int> bombLocation, CCoord<int> direction, unsigned int explosionRadius)
{
    for (unsigned int i = 0; i <= explosionRadius; i++)
    {
        CCoord<unsigned int> locationToExplode = (bombLocation.ToDouble() + (i * direction).ToDouble()).ToUnsignedInt();

        // Target exists and its not destructible.
        CBlock *target = this->GetMapItem(locationToExplode);
        if ((target && !target->IsDestructible()))
        { break; /* Leave for loop - The wave was stopped by this indestructible wall.*/        }

        bool wallDestroyed = false;

        if (target)
        {
            if (target->TryDestroy(i) && !target->IsAlive())
            {
                wallDestroyed = true;
            } else if (!target->IsAlive())
            { break;  /* Leave for loop - The wave was stopped by this wall.*/            }
        }

        // Find collectible in location to explode.
        auto foundCollectible = this->m_Collectibles.find(
                locationToExplode.ToUnsignedInt());
        if (foundCollectible != this->m_Collectibles.end())
        { break; /* leave for loop - We dont want burning collectibles*/        }

        // Create new fire.
        CFire *fire = new CFire(this->m_FireObjectTexturePack, this->m_FireObjectTexturePack->GetTextureSize());
        this->SetMapItem(fire, locationToExplode);

        if (wallDestroyed)
        { break; /* Explosion was stopped by destroyed wall. */ }
    }
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
void CBoard::Draw(CSDLInterface &interface, CCoord<> offset)
{
    // draw map
    for (size_t i = 0; i < this->m_BoardSize.m_X; i++)
    {
        for (size_t j = 0; j < this->m_BoardSize.m_Y; j++)
        {
            // Draw background and the object.
            if (this->m_GroundObject)
            { this->m_GroundObject->Draw(interface, this->m_CellSize, CCoord<unsigned int>(i, j).ToDouble(), offset); }
            if (this->m_Map[i][j])
            { this->m_Map[i][j]->Draw(interface, this->m_CellSize, CCoord<unsigned int>(i, j).ToDouble(), offset); }
        }
    }

    for (auto i = this->m_GameObjects.begin(); i != this->m_GameObjects.end(); i++)
    {
        if (*i)
        { (*i)->Draw(interface, this->m_CellSize, (*i)->GetLocation(), offset); }
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
            interface.RenderRectangle(&rect);
        }
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
            // Update if object is alive.
            if (this->m_Map[i][j])
            {
                auto bomb = this->m_BombsToExplode.find((this->m_Map[i][j]));

                if (bomb != this->m_BombsToExplode.end())
                { this->CreateExplosion((*bomb), CCoord<unsigned int>(i, j)); }
                else if (this->m_Map[i][j]->IsAlive())
                { this->m_Map[i][j]->Update(*this, deltaTime); }
            }
            // Delete dead objects.
            if (this->m_Map[i][j] && !this->m_Map[i][j]->IsAlive())
            {
                delete this->m_Map[i][j];
                this->m_Map[i][j] = nullptr;
            }
        }
    }

    /* std::vector<std::size_t> objectsToRemove;
     for (auto i = this->m_GameObjects.begin(); i != this->m_GameObjects.end(); i++)
     {
         if (*i && (*i)->IsAlive())
         { (*i)->Update(*this, deltaTime); }
     }*/

    // Update players
    for (size_t i = 0; i < this->m_Players.size(); i++)
    { this->m_Players[i]->Update(*this, deltaTime); }

    // Update collectibles
    for (auto i = this->m_Collectibles.begin(); i != this->m_Collectibles.end();/* i++*/)
    {
        // Save iterator to next object because current bomb could be removed in Update().
        auto item = i++;
        if (item->second)
        { item->second->Update(*this, deltaTime); }
        else
        {
            // Remove null item
            this->m_Collectibles.erase(item);
        }
    }
}

/*====================================================================================================================*/
void CBoard::UpdatePhysicEvents()
{
    CCoord<int> directions[5] = {CCoord<int>(0,0), CCoord<int>(0, 1), CCoord<int>(0, -1), CCoord<int>(1, 0), CCoord<int>(-1, 0)};
    for (auto player = this->m_Players.begin(); player != this->m_Players.end(); player++)
    {
        if ((*(player)) && (*(player))->IsAlive())
        {
            CCoord<unsigned int> playerCenterCell = (*player)->GetLocationCell();

            // Check collisions with objects around the player.
            for (unsigned int i = 0; i < 5; i++)
            {
                CCoord<unsigned int> blockLocation = (playerCenterCell.ToInt() + directions[i]).ToUnsignedInt();
                CBlock *block = this->GetMapItem(blockLocation);
                if (block)
                { block->PlayerCollision(blockLocation, *(*player)); }
            }
        }


        return;

        /* for (auto object = this->m_GameObjects.begin(); object != this->m_GameObjects.end(); object++)
    {
        // Resolving a potential collision with an object.
        //  if((*object) && (*object)->IsAlive())
        //  {(*player)->CollisionWith(*(*object));}
    }*/

        // Collectible collision - Apply collectible on the player.
        for (auto collectible = this->m_Collectibles.begin();
             collectible != this->m_Collectibles.end(); collectible++)
        {
            if (collectible->second && collectible->second->IsVisible() &&
                (*player)->IsColliding(collectible->second))
            {
                // Polymorphic call
                collectible->second->Apply((*player)); // Apply item
            }
        }

        // Fire collision - Kill the player.
        /* for (auto fire = this->m_Fires.begin(); fire != this->m_Fires.end(); fire++)
         {
                // Kill player if player is colliding fire and do he does not have fire imunity.
                if (fire->second && !(*player)->GetFireImunity() && (*player)->IsColliding(fire->second))
                { (*player)->Kill(); }
         }*/

        // Enemy collision - Kill the player.
        /*for (auto enemy = this->m_Enemies.begin(); enemy != this->m_Enemies.end(); enemy++)
        {
            if (*enemy && (*enemy)->IsAlive() &&
                (*player)->IsColliding((*enemy)))
            { (*player)->Kill(); }
        }*/
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

    for (auto object = this->m_GameObjects.begin(); object != this->m_GameObjects.end(); object++)
    {
        if (clearLevelObjects)
        { delete (*object); }
        /*else
        {(*object)->Reset(*this);}*/
    }

    if (clearLevelObjects)
    { this->m_GameObjects.clear(); }

    // Rerun players locations
    for (size_t i = 0; i < this->m_Players.size(); i++)
    { this->m_Players[i]->Reset(*this); }
}

/*====================================================================================================================*/
bool CBoard::PositionFree(CCoord<unsigned int> coord)
{
    CBlock *block = this->GetMapItem(coord);

    // Check walls
    if (block != nullptr ||
        this->m_Collectibles.find(coord) != this->m_Collectibles.end())
    { return false; }

    for (size_t i = 0; i < this->m_Players.size(); i++)
    {
        if (m_Players[i]->GetLocation().AlmostEqual(coord.ToDouble()))
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
    for (unsigned int i = 0; i <= CBoard::PLAYER_SAVE_ZONE; i++)
    {
        CCoord<> curLocation = (player->GetLocation() + (direction * i).ToDouble());

        if (curLocation == location.ToDouble())
        { return false; }
    }

    return true;
}

/*====================================================================================================================*/
CBlock *CBoard::GetMapItem(CCoord<unsigned int> location)
{
    if (location.m_X < 0 || location.m_X >= CBoard::m_BoardSize.m_X ||
        location.m_Y < 0 || location.m_Y >= CBoard::m_BoardSize.m_Y)
    { throw std::out_of_range(MESSAGE_INDEX_OUT_OF_BOUND); }

    return this->m_Map[location.m_X][location.m_Y];
}

/*====================================================================================================================*/
void CBoard::SetMapItem(CBlock *block, CCoord<unsigned int> location)
{
    if (location.m_X < 0 || location.m_X >= CBoard::m_BoardSize.m_X ||
        location.m_Y < 0 || location.m_Y >= CBoard::m_BoardSize.m_Y)
    { throw std::out_of_range(MESSAGE_INDEX_OUT_OF_BOUND); }

    // Kill and delete old block.
    if (this->m_Map[location.m_X][location.m_Y])
    {
        this->m_Map[location.m_X][location.m_Y]->Kill();
        delete this->m_Map[location.m_X][location.m_Y];
    }

    this->m_Map[location.m_X][location.m_Y] = block;
}
