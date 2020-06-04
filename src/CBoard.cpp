/**
 * @author Jaroslav Fikar
 * 
*/


#include <chrono>
#include "CBoard.h"

CBoard::~CBoard()
{
    for (size_t i = 0; i < this->m_BoardSize.m_X; i++)
    {
        for (size_t j = 0; j < this->m_BoardSize.m_Y; j++)
        {
            delete this->m_Map[i][j];
        }
    }

    for (size_t i = 0; i < this->m_Players.size(); i++)
    {
        delete this->m_Players[i];
    }

    for (auto i = this->m_Bombs.begin(); i != this->m_Bombs.end(); i++)
    {
        // Polymorphic call
        delete i->second;
    }

    for (auto i = this->m_Fires.begin(); i != this->m_Fires.end(); i++)
    {
        // Polymorphic call
        delete i->second;
    }

    delete (this->m_GroundObject);
}

/*====================================================================================================================*/
bool CBoard::IsPassable(CCoord coord, const CPlayer *player)
{
    // Array index check.
    if (coord.m_X < 0 || coord.m_X >= CBoard::m_BoardSize.m_X ||
        coord.m_Y < 0 || coord.m_Y >= CBoard::m_BoardSize.m_Y)
    {
        throw std::out_of_range(MESSAGE_INDEX_OUT_OF_BOUND);
    }

    CGameObject *gameObject = this->m_Map[static_cast<int>(floor(coord.m_X))][static_cast<int>( floor(coord.m_Y))];

    if (gameObject && gameObject->IsAlive())
    {
        return false;
    }

    // Search for bombs in location.
    auto bomb = this->m_Bombs.find(CCoord(static_cast<int>(floor(coord.m_X)), static_cast<int>(floor(coord.m_Y))));
    if (bomb != this->m_Bombs.end() && bomb->second && player->IsColiding(bomb->second))
    {
        // Player is not owner or the bomb is not passable for owner
        if (bomb->second->GetOwner() != player || !bomb->second->IsPassableForOwner())
        {
            return false;
        }
    }

    return true;
    // todo other gameobjests
}

/*====================================================================================================================*/
void CBoard::PlaceBomb(CPlayer *player)
{
    CCoord location = player->GetLocationCell();

    // If this location is free.
    if (this->m_Bombs.find(location) == this->m_Bombs.end() && this->m_Fires.find(location) == this->m_Fires.end())
    {
        CBomb *bomb = new CBomb(this->m_BombObjectTexturePack, this->m_BombObjectTexturePack->GetTextureSize(),
                                location, player);

        this->m_Bombs.insert(std::pair<CCoord, CBomb *>(location, bomb));
    }
}


/*====================================================================================================================*/
void CBoard::DetonateBombs(const CPlayer *player)
{
    for (auto i = this->m_Bombs.begin(); i != this->m_Bombs.end(); i++)
    {
        if (i->second->GetOwner() == player)
        {
            i->second->Detonate(this);
        }
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
            CCoord directions[4] = {CCoord(0, 1), CCoord(0, -1), CCoord(1, 0), CCoord(-1, 0)};
            for (int i = 0; i < 4; i++)
            {
                this->CreateExplosionWave(bomb, directions[i], explosionRadius);
            }
        }

        CCoord location = bomb->GetLocation();
        auto bombToRemove = this->m_Bombs.find(location);
        if (bombToRemove != this->m_Bombs.end())
        {
            delete bombToRemove->second;
            bombToRemove->second = nullptr;
            this->m_Bombs.erase(bombToRemove);
        }
            // Error message when the bomb is not found - this should never happen
        else
        {
            std::cerr << "Bomb " << location << " not found " << std::endl;
        }
    }
}

/*====================================================================================================================*/
void CBoard::CreateExplosionWave(CBomb *bomb, CCoord direction, unsigned int explosionRadius)
{
    for (unsigned int i = 0; i <= explosionRadius; i++)
    {
        CCoord locationToExplode = bomb->GetLocation() + (i * direction);

        if (locationToExplode.m_X < 0 || locationToExplode.m_X >= CBoard::m_BoardSize.m_X ||
            locationToExplode.m_Y < 0 || locationToExplode.m_Y >= CBoard::m_BoardSize.m_Y)
        {
            throw std::out_of_range(MESSAGE_INDEX_OUT_OF_BOUND);
        }

        // Target exists and its not destructible.
        CWall *target = this->m_Map[static_cast<int>(locationToExplode.m_X)][static_cast<int>(locationToExplode.m_Y)];
        if ((target && !target->IsDestructible()))
        {
            return;
        }

        if (target)
        {
            if (target->TryDestroy(i))
            {
                delete target;
                this->m_Map[static_cast<int>(locationToExplode.m_X)][static_cast<int>(locationToExplode.m_Y)] = nullptr;
            }
        }

        // Destroy potencialy existing fire is this location
        auto foundFire = this->m_Fires.find(locationToExplode);
        if (foundFire != this->m_Fires.end())
        {
            // Remove old fire.
            delete (foundFire->second);
            foundFire->second = nullptr;
            this->m_Fires.erase(foundFire);
        }

        // Create new fire
        CFire *fire = new CFire(this->m_FireObjectTexturePack, this->m_FireObjectTexturePack->GetTextureSize(),
                                locationToExplode);
        this->m_Fires.insert(std::pair<CCoord, CFire *>(locationToExplode, fire));
    }
}

/*====================================================================================================================*/
void CBoard::DestroyExplosion(CFire *fire)
{
    CCoord fireLocation = fire->GetLocation();
    auto fireToRemove = this->m_Fires.find(fireLocation);
    if (fireToRemove != this->m_Fires.end())
    {
        delete (fireToRemove->second);
        fireToRemove->second = nullptr;
        this->m_Fires.erase(fireToRemove);
    }
        // Error message when the fire is not found - this should never happen
    else
    {
        std::cerr << "Fire " << fireLocation << " not found " << std::endl;
    }
}

/*====================================================================================================================*/
void CBoard::Draw(CSDLInterface *interface, CCoord offset)
{
    // TODO debug

    // Draw debug lines
    /*  interface->SetRenderColor(128, 0, 0, 255);
      for (double i = 0; i < interface->GetWindowSize().m_Y; i++)
      {
          interface->RenderLine(CCoord(0, 25 * i), CCoord(interface->GetWindowSize().m_X, 25 * i));
      }

      for (double i = 0; i < interface->GetWindowSize().m_X - 1; i++)
      {
          interface->RenderLine(CCoord(25 * i, 0), CCoord(25 * i, interface->GetWindowSize().m_Y));
      }*/

    // draw map
    for (size_t i = 0; i < this->m_BoardSize.m_X; i++)
    {
        for (size_t j = 0; j < this->m_BoardSize.m_Y; j++)
        {
            if (this->m_Map[i][j])
            {
                this->m_Map[i][j]->Draw(interface, this->m_CellSize, CCoord(i, j), offset);
            } else if (this->m_GroundObject)
            {
                this->m_GroundObject->Draw(interface, this->m_CellSize, CCoord(i, j), offset);
            }
        }
    }

    // Draw enemies
    for (size_t i = 0; i < this->m_Enemies.size(); i++)
    {
        if (this->m_Enemies[i])
        {
            this->m_Enemies[i]->Draw(interface, this->m_CellSize, this->m_Enemies[i]->GetLocation(), offset);
        }
    }

    // draw boosts
    for (auto i = this->m_Boosts.begin(); i != this->m_Boosts.end(); i++)
    {
        if (i->second)
        {
            i->second->Draw(interface, this->m_CellSize, i->first, offset);
        }
    }

    // draw bombs
    for (auto i = this->m_Bombs.begin(); i != this->m_Bombs.end(); i++)
    {
        if (i->second)
        {
            i->second->Draw(interface, this->m_CellSize, i->first, offset);
        }
    }

    // draw fires
    for (auto i = this->m_Fires.begin(); i != this->m_Fires.end(); i++)
    {
        if (i->second)
        {
            i->second->Draw(interface, this->m_CellSize, i->first, offset);
        }
    }

    // TODO změnit pořadí renderu tak, aby nejdříve byly renderovány objekty, které jsou vespod.
    // draw players
    for (size_t i = 0; i < this->m_Players.size(); i++)
    {
        if (this->m_Players[i])
        {
            this->m_Players[i]->Draw(interface, this->m_CellSize, this->m_Players[i]->GetLocation(), offset);
        }
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
            if (this->m_Map[i][j] && this->m_Map[i][j]->IsAlive())
            {
                this->m_Map[i][j]->Update(this, deltaTime);
            }
                // destroy if is dead (TODO this will be problem with dying animations)
            else
            {
                delete this->m_Map[i][j];
            }
        }
    }

    // Update players
    for (size_t i = 0; i < this->m_Players.size(); i++)
    {
        this->m_Players[i]->Update(this, deltaTime);
    }

    // Update enemies
    for (size_t i = 0; i < this->m_Enemies.size(); i++)
    {
        // Polymorphic call
        this->m_Enemies[i]->Update(this, deltaTime);
    }

    // Update boosts
    for (auto i = this->m_Boosts.begin(); i != this->m_Boosts.end(); i++)
    {
        // Polymorphic call
        i->second->Update(this, deltaTime);
    }

    // Update bombs
    for (auto i = this->m_Bombs.begin(); i != this->m_Bombs.end();/* i++*/)
    {
        // Save iterator to next object because current bomb could be removed in Update().
        auto item = i++;
        if (item->second)
        {
            item->second->Update(this, deltaTime);
        } else
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
        {
            item->second->Update(this, deltaTime);
        } else
        {
            // Remove null item
            this->m_Fires.erase(item);
        }
    }
}

/*====================================================================================================================*/
void CBoard::UpdatePhysics()
{
    /* if({somePlayer} is coliding {someBoost} ))
     {
         // Polymorphic call
          {someBoost}->Apply({somePlayer});
     }*/

    for (auto player = this->m_Players.begin(); player != this->m_Players.end(); player++)
    {
        for (auto fire = this->m_Fires.begin(); fire != this->m_Fires.end(); fire++)
        {
            // Kill player if player is valid pointer and colliding fire.
            if (player.base() && (*(player.base()))->IsAlive() && fire->second &&
                (*(player.base()))->IsColiding(fire->second))
            {
                std::cout << std::chrono::duration_cast<std::chrono::seconds>(
                        std::chrono::system_clock::now().time_since_epoch()).count() << " Player is killed."
                          << std::endl;
                (*(player.base()))->Kill();
               // return this->RoundOver((*(player.base())));
            }
        }
    }

   // return EGameStatus::GAMESTATUS_RUNNING;
}

/*====================================================================================================================*/
EGameStatus CBoard::RoundOver(CPlayer *player)
{
    if (player->GetLives() < 0)
    {
        return EGameStatus::GAME_STATUS_GAME_OVER;
    }

    return EGameStatus::GAMESTATUS_ROUND_OVER;
}

/*====================================================================================================================*/
void CBoard::ClearBoard()
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

    // Delete enemies
    for (size_t i = 0; i < this->m_Enemies.size(); i++)
    {
        delete this->m_Enemies[i];
    }
    this->m_Enemies.clear();

    // Delete boosts
    for (auto i = this->m_Boosts.begin(); i != this->m_Boosts.end(); i++)
    {
        delete (i->second);
        i->second = nullptr;
    }
    this->m_Boosts.clear();

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
    {
        this->m_Players[i]->Reset();
    }
}

/*====================================================================================================================*/
bool CBoard::PositionFree(CCoord coord)
{
    if (coord.m_X < 0 || coord.m_X >= CBoard::m_BoardSize.m_X ||
        coord.m_Y < 0 || coord.m_Y >= CBoard::m_BoardSize.m_Y)
    {
        throw std::out_of_range(MESSAGE_INDEX_OUT_OF_BOUND);
    }

    // Check walls
    if (this->m_Map[static_cast<int>(coord.m_X)][static_cast<int>(coord.m_Y)] != nullptr ||
        this->m_Bombs.find(coord) != this->m_Bombs.end() ||
        this->m_Fires.find(coord) != this->m_Fires.end() ||
        this->m_Boosts.find(coord) != this->m_Boosts.end())
    {
        return false;
    }

    for (size_t i = 0; i < this->m_Players.size(); i++)
    {
        if (m_Players[i]->GetLocation().AlmostEqual(coord))
        {
            return false;
        }
    }

    for (size_t i = 0; i < this->m_Enemies.size(); i++)
    {
        if (m_Enemies[i]->GetLocation().AlmostEqual(coord))
        {
            return false;
        }
    }

    return true;
}

/*====================================================================================================================*/
bool CBoard::PlayersAreaFree(CCoord coord)
{
    // Create direction vectors.
    CCoord directions[4] = {CCoord(0, 1), CCoord(0, -1), CCoord(1, 0), CCoord(-1, 0)};

    for (std::vector<CPlayer *>::size_type i = 0; i < this->m_Players.size(); i++)
    {
        for (unsigned int j = 0; j < 4; j++)
        {
            if (!this->PlayerDirectionFree(coord, this->m_Players[i], directions[j]))
            {
                return false;
            }
        }
    }

    return true;
}

/*====================================================================================================================*/
bool CBoard::PlayerDirectionFree(CCoord location, CPlayer *player, CCoord direction)
{
    for (unsigned int i = 0; i <= player->GetExplosionRadius(); i++)
    {
        CCoord curLocation = (player->GetLocation() + (direction * i));

        if (curLocation == location)
        {
            return false;
        }
    }

    return true;
}












