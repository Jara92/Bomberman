/**
 * @author Jaroslav Fikar
*/

#include "CBoard.h"

CBoard::~CBoard()
{
    for (size_t i = 0; i < this->m_BoardSize.m_X; i++)
    {
        for (size_t j = 0; j < this->m_BoardSize.m_Y; j++)
        {
            if (this->m_Map[i][j])
            {
                // Delete collectible (Collectible may be attached to CWall or a Collectible may be directly in 2D array)
                CCollectible *collectible = this->m_Map[i][j]->GetCollectible();
                if (collectible)
                { delete collectible; }

                // Delete collectible parent if it has parent.
                if (this->m_Map[i][j] != collectible)
                {
                    delete this->m_Map[i][j];
                    this->m_Map[i][j] = nullptr;
                }

            }
        }
    }
    this->m_Map.clear();

    for (size_t i = 0; i < this->m_Movables.size(); i++)
    { delete this->m_Movables[i]; }
    this->m_Movables.clear();

    for (size_t i = 0; i < this->m_Players.size(); i++)
    { delete this->m_Players[i]; }
    this->m_Players.clear();
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

    for (auto i = this->m_Movables.begin(); i != this->m_Movables.end(); i++)
    {
        if (*i)
        { (*i)->Draw(interface, this->m_CellSize, offset); }
    }

    // TODO změnit pořadí renderu tak, aby nejdříve byly renderovány objekty, které jsou vespod.
    // draw players
    for (size_t i = 0; i < this->m_Players.size(); i++)
    {
        if (this->m_Players[i])
        { this->m_Players[i]->Draw(interface, this->m_CellSize, offset); }
    }
}

/*====================================================================================================================*/
void CBoard::Update(int deltaTime)
{
    // Update map.
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
                if (this->m_Map[i][j]->HasCollectible() && this->m_Map[i][j] != this->m_Map[i][j]->GetCollectible() &&
                    this->m_Map[i][j]->GetCollectible())
                { this->SetMapItem(this->m_Map[i][j]->GetCollectible(), CCoord<unsigned int>(i, j)); }
                else
                { this->SetMapItem(nullptr, CCoord<unsigned int>(i, j)); }
            }
        }
    }

    // Update movables objects.
    for (auto item = this->m_Movables.begin(); item != this->m_Movables.end(); /* item++*/)
    {
        // Save iterator to current item and increment control variable.
        auto currentItem = item++;
        if (*currentItem && (*currentItem)->IsAlive())
        { (*currentItem)->Update(*this, deltaTime); }
            // Remove nullptr or dead item.
        else
        { this->m_Movables.erase(currentItem); }
    }

    // Update players
    for (size_t i = 0; i < this->m_Players.size(); i++)
    { this->m_Players[i]->Update(*this, deltaTime); }
}

/*====================================================================================================================*/
bool CBoard::IsPassable(CCoord<unsigned int> coord, const CMovable &movable)
{
    CBlock *block = this->GetMapItem(coord);

    if (block && block->IsAlive() && !block->IsPassable(coord, movable))
    { return false; }

    return true;
}

/*====================================================================================================================*/
bool CBoard::PlaceBomb(CPlayer *player)
{
    CCoord<unsigned int> location = player->GetLocationCell();

    // We do not want to plant bombs on a wall.
    if (this->GetMapItem(location) != nullptr)
    { return false; }

    // Set explosion delay.
    int delay = (player->GetRemoteExplosion() ? CBomb::TRIGGER_EXPLOSION_DELAY : CBomb::AUTO_EXPLOSION_DELAY);

    CBomb *bomb = new CBomb(this->m_BombObjectTexturePack,
                            this->m_BombObjectTexturePack->GetTextureSize() + CCoord<>(0.05, 0.05), player,
                            delay, player->GetRemoteExplosion());
    this->SetMapItem(bomb, location);

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
                if (target->HasCollectible())
                { break; /* Leave for loop - The wave was stopped by targets attached collectible object. */ }
                wallDestroyed = true;
            } else if (!target->IsAlive())
            { break;  /* Leave for loop - The wave was stopped by this wall.*/            }
        }

        // Create new fire.
        CFire *fire = new CFire(this->m_FireObjectTexturePack, this->m_FireObjectTexturePack->GetTextureSize());
        this->SetMapItem(fire, locationToExplode);

        if (wallDestroyed)
        { break; /* Explosion was stopped by destroyed wall. */ }
    }
}

/*====================================================================================================================*/
void CBoard::UpdatePhysicEvents()
{
    CCoord<int> directions[5] = {CCoord<int>(0, 0), CCoord<int>(0, 1), CCoord<int>(0, -1), CCoord<int>(1, 0),
                                 CCoord<int>(-1, 0)};
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
    }
}

/*====================================================================================================================*/
void CBoard::PrepareBoard(bool clearLevelObjects, std::vector<CCollectible *> &collectibles)
{
    // Delete walls
    for (size_t i = 0; i < this->m_BoardSize.m_X; i++)
    {
        for (size_t j = 0; j < this->m_BoardSize.m_Y; j++)
        {
            CBlock *item = this->GetMapItem(CCoord<unsigned int>(i, j));
            if (item && item->HasCollectible())
            {
                // Insert every CCollectible in vector.
                collectibles.push_back(item->GetCollectible());
                if (item == item->GetCollectible())
                {
                    // Remove CCollectible block from 2D array but we do not want to delete it. We may use it later.
                    this->m_Map[i][j] = nullptr;
                    item = nullptr;
                }
            }

            // Delete every destructible objects.
            if (this->m_Map[i][j] && this->m_Map[i][j]->IsDestructible())
            {
                delete this->m_Map[i][j];
                this->m_Map[i][j] = nullptr;
            }
        }
    }

    for (auto object = this->m_Movables.begin(); object != this->m_Movables.end(); object++)
    {
        if (clearLevelObjects)
        { delete (*object); }
        /*else
        {(*object)->Reset(*this);}*/
    }

    if (clearLevelObjects)
    { this->m_Movables.clear(); }

    // Rerun players locations
    for (size_t i = 0; i < this->m_Players.size(); i++)
    { this->m_Players[i]->Reset(*this); }

    this->m_BombsToExplode.clear();
}

/*====================================================================================================================*/
bool CBoard::PositionFree(CCoord<unsigned int> coord)
{
    CBlock *block = this->GetMapItem(coord);

    // Check walls
    if (block != nullptr)
    { return false; }

    return true;
}

/*====================================================================================================================*/
bool CBoard::PlayersAreaFree(CCoord<unsigned int> coord, double playerSaveZone)
{
    for (std::vector<CPlayer *>::size_type i = 0; i < this->m_Players.size(); i++)
    {
        if (this->m_Players[i]->GetLocation().CalcDistnance(coord.ToDouble()) < playerSaveZone)
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
/*====================================================================================================================*/
void CBoard::DestroyEveryDestructibleWall()
{
    for (unsigned int i = 0; i < this->GetBoardSize().m_X; i++)
    {
        for (unsigned int j = 0; j < this->GetBoardSize().m_Y; j++)
        {
            if (this->m_Map[i][j] && this->m_Map[i][j]->TryDestroy(0))
            {
                // Destroy detructible wall and plant collectible.
                CCoord<unsigned int> itemLocation = CCoord<unsigned int>(i, j);
                if (this->GetMapItem(itemLocation)->HasCollectible() &&
                    this->GetMapItem(itemLocation)->GetCollectible())
                { this->SetMapItem(this->GetMapItem(itemLocation)->GetCollectible(), itemLocation); }
                    // Destroy the wall.
                else
                { this->SetMapItem(nullptr, itemLocation); }
            }
        }
    }
}
