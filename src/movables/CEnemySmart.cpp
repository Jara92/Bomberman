/**
 * @author Jaroslav Fikar
*/

#include "CEnemySmart.h"
#include "../CBoard.h"

void CEnemySmart::Update(CBoard &board, int deltaTime)
{
    CEnemy::Update(board, deltaTime);

    // Move when the enemy is alive.
    if (this->m_IsAlive)
    {
        CCoord<> oldLocation = this->m_Location;

        this->Move(board, deltaTime);

        this->UpdateTextureType(oldLocation);
    }
}

/*====================================================================================================================*/
void CEnemySmart::UpdateMovementMode()
{

    /*  int actualMovementMode = static_cast<int>(this->m_MovementMode);
      int newMovementMode = 0;

      if (actualMovementMode < static_cast<int>(EEnemyMovementMode::ENEMY_MOVEMENT_MODE_NR_ITEMS) - 1)
      { newMovementMode = actualMovementMode + 1; }

      this->m_MovementMode = static_cast<EEnemyMovementMode >(newMovementMode);
      std::cout << "new mode " << newMovementMode << std::endl;
      this->m_MovementMode = EEnemyMovementMode::ENEMY_MOVEMENT_MODE_FOLLOW_THE_PLAYER;

      this->m_MovementModeTimer.Reset();*/
}

/*====================================================================================================================*/

void CEnemySmart::Move(const CBoard &board, int deltaTime)
{
    this->m_MovementMode = EEnemyMovementMode::ENEMY_MOVEMENT_MODE_FOLLOW_THE_PLAYER; // FIXME REMOVE

    for (int i = 0; i < deltaTime; i++)
    {
        this->FollowThePlayer(board);
        continue;
        /*if (this->m_MovementMode == EEnemyMovementMode::ENEMY_MOVEMENT_MODE_FOLLOW_THE_PLAYER)
        { ;
            continue;}*/

        if (this->m_MovementMode == EEnemyMovementMode::ENEMY_MOVEMENT_MODE_WALK_RANDOM && this->TurnRandom(board))
        { continue; }
        else if (this->GoForward(board))
        { continue; }
        else
        { this->GoRandom(board); }
    }
}

/*====================================================================================================================*/
bool CEnemySmart::FollowThePlayer(const CBoard &board)
{
    if (!this->m_PersecutedPlayer)
    {
        unsigned int randomPlayer = CRandom::Random(0, board.m_Players.size());
        this->m_PersecutedPlayer = board.m_Players[randomPlayer];
    }

    auto targetLocation = this->m_PersecutedPlayer->GetLocationCell();

    this->m_Movement = this->FindWayToLocation(board, targetLocation);

   /* auto directions = this->GetPossibleMoveDirections(board);

    for (int i = 0; i < directions.size(); i++)
    {
        bool found = this->FindWayToLocationRec(0, board, this->GetLocationCell(), this->GetLocationCell(),
                                                targetLocation);
        if (found)
        {
            this->m_Movement = directions[i];
            break;
        }
    }*/


    return this->GoForward(board);
}

/*====================================================================================================================*/
CCoord<> CEnemySmart::FindWayToLocation(const CBoard &board, CCoord<unsigned int> location)
{

    //bool map[board.GetBoardSize().m_X][board.GetBoardSize().m_Y];
    std::vector<std::vector<bool>> map;
    map.resize(board.GetBoardSize().m_X);
    for(int i = 0; i < board.GetBoardSize().m_X;i++)
    {
        map[i].resize(board.GetBoardSize().m_Y);
    }

    for (unsigned int i = 0; i < board.GetBoardSize().m_X; i++)
    {
        for (unsigned int j = 0; j < board.GetBoardSize().m_Y; j++)
        {
            auto loc = CCoord<unsigned int>(i, j);

            if (!board.GetMapItem(loc) || board.GetMapItem(loc)->IsPassable(loc, *this))
            { map[i][j] = true; }
            else
            { map[i][j] = false; }
            // std::cout << map[i][j];
        }
        // std::cout << std::endl;
    }

    auto a = this->findPath(map, this->GetLocationCell(), location);



    if(!a.empty())
    {return (a[0]).ToDouble();}



    return CCoord<>(0,0);

}

bool CEnemySmart::FindWayToLocationRec(std::vector<std::vector<bool>> map, CCoord<unsigned int> oldLocation,
                                       CCoord<unsigned int> currentLocation,
                                       CCoord<unsigned int> targetLocation)
{
   /* std::vector<CCoord<int>> directions = {{0, 1},
                                           {0, -1},
                                           {1, 0},
                                           {-1, 0}};

    for (int i = 0; i < directions.size(); i++)
    {
        CCoord<unsigned int> loc = (currentLocation.ToInt() + directions[i]).ToUnsignedInt();

        if (loc == oldLocation)
        { continue; }

        if (loc == targetLocation)
        { return true; }

        else if (board.GetMapItem(loc) == nullptr || board.GetMapItem(loc)->IsPassable(loc, *this))
        {
            std::cout << loc << std::endl;
            bool found = (this->FindWayToLocationRec(0, board, loc, currentLocation, targetLocation));

            if (found)
            {
                std::cout << "found" << std::endl;
                return true;
            }
        }
    }

    return false;*/
}

