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
    if (bomb != this->m_Bombs.end() && player->IsColiding(bomb->second, CBomb::COLLISION_TOLERANCE))
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
    if (this->m_Bombs.find(location) == this->m_Bombs.end())
    {
        CBomb *bomb = new CBomb(this->m_BombObjectTexturePack, location, player);

        this->m_Bombs.insert(std::pair<CCoord, CBomb *>(location, bomb));
    }
}


/*====================================================================================================================*/
void CBoard::DetonateBombs(const CPlayer *player)
{

}

/*====================================================================================================================*/
void CBoard::CreateExplosion(CBomb *bomb)
{
    if (bomb)
    {
        CCoord location = bomb->GetLocation();
        CPlayer *owner = bomb->GetOwner();

        if (owner)
        {
            unsigned int explosionRadius = owner->GetExplosionRadius();

            // Explosion in all directions.
            CCoord directions[4] = {CCoord(0, 1), CCoord(0, -1), CCoord(1, 0), CCoord(-1, 0)};
            for (int i = 0; i < 4; i++)
            {
                this->CreateExplosionWave(location, directions[i], explosionRadius);
            }
        }

        auto bombToRemove = this->m_Bombs.find(bomb->GetLocation());
        if (bombToRemove != this->m_Bombs.end())
        {
            delete bombToRemove->second;
            //bombToRemove->second = nullptr;
            this->m_Bombs.erase(bomb->GetLocation());
        }
    }
}

/*====================================================================================================================*/
void CBoard::CreateExplosionWave(CCoord location, CCoord direction, unsigned int explosionRadius)
{
    for (int i = 0; i <= explosionRadius; i++)
    {
        CCoord locationToExplode = location + (i * direction);

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
            target->TryDestroy(i);
            delete target;
            this->m_Map[static_cast<int>(locationToExplode.m_X)][static_cast<int>(locationToExplode.m_Y)] = nullptr;
        }

        CFire *fire = new CFire(this->m_FireObjectTexturePack, locationToExplode);
        this->m_Fires.insert(std::pair<CCoord, CFire *>(locationToExplode, fire));
    }
}

/*====================================================================================================================*/
void CBoard::DestroyExplosion(CFire *fire)
{
    auto fireToRemove = this->m_Fires.find(fire->GetLocation());
    if (fireToRemove != this->m_Fires.end())
    {
        delete fireToRemove->second;
        this->m_Fires.erase(fire->GetLocation());
    }

}

/*====================================================================================================================*/
void CBoard::Draw(CSDLInterface *interface)
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
                this->m_Map[i][j]->Draw(interface, this->m_CellSize, CCoord(i, j));
            } else if (this->m_GroundObject)
            {
                this->m_GroundObject->Draw(interface, this->m_CellSize, CCoord(i, j));
            }
        }
    }

    // Draw enemies
    for (size_t i = 0; i < this->m_Enemies.size(); i++)
    {
        // Polymorphic call
        this->m_Enemies[i]->Draw(interface, this->m_CellSize);
    }

    // draw boosts
    for (auto i = this->m_Boosts.begin(); i != this->m_Boosts.end(); i++)
    {
        // Polymorphic call
        i->second->Draw(interface, this->m_CellSize, i->first);
    }

    // draw bombs
    for (auto i = this->m_Bombs.begin(); i != this->m_Bombs.end(); i++)
    {
        // Polymorphic call
        i->second->Draw(interface, this->m_CellSize, i->first);
    }

    // draw fires
    for (auto i = this->m_Fires.begin(); i != this->m_Fires.end(); i++)
    {
        // Polymorphic call
        i->second->Draw(interface, this->m_CellSize, i->first);
    }

    // TODO změnit pořadí renderu tak, aby nejdříve byly renderovány objekty, které jsou vespod.
    // draw players
    for (size_t i = 0; i < this->m_Players.size(); i++)
    {
        this->m_Players[i]->Draw(interface, this->m_CellSize);
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
    for (auto i = this->m_Bombs.begin(); i != this->m_Bombs.end(); i++)
    {
        // Polymorphic call
        i->second->Update(this, deltaTime);
    }

    // Update fires
    for (auto i = this->m_Fires.begin(); i != this->m_Fires.end(); i++)
    {
        // Polymorphic call
        i->second->Update(this, deltaTime);
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

    /*for (auto i = this->m_Bombs.begin(); i != this->m_Bombs.end(); i++)
    {
        CPlayer * owner = i->second->GetOwner();

        if(owner && !owner->IsColiding(owner->GetLocation(), i->second, i->first))
        {
            std::cout << "unpass" << std::endl;
            i->second->MakeUnpassableForOwner();
        }
    }*/
}

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

    // Reset players locations
    for (size_t i = 0; i < this->m_Players.size(); i++)
    {
        this->m_Players[i]->ResetLocation();
    }
}

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
        this->m_Boosts.find(coord) != this->m_Boosts.end() ||
        this->m_Fires.find(coord) != this->m_Fires.end())
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









