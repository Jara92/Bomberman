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
    std::cout << "Movement " << this->m_Movement << std::endl;

    return this->GoForward(board);
}

/*====================================================================================================================*/
CCoord<> CEnemySmart::FindWayToLocation(const CBoard &board, CCoord<unsigned int> location)
{
    if (this->m_PathToPlayer.empty())
    {
        this->FindPathTo(board, this->GetLocationCell(), location);

        if (this->m_PathToPlayer.empty())
        { return CCoord<>(0, 0); }
    }

    if (this->GetLocation().AlmostEqual(this->m_PathToPlayer[0].ToDouble(), this->m_Speed))
    {
        // Calibrate enemies location.
        this->m_Location = this->m_PathToPlayer[0].ToDouble();
        this->m_PathToPlayer.erase(this->m_PathToPlayer.begin());
        this->m_DirectionsToPlayer.erase(this->m_DirectionsToPlayer.begin());
    }

    if (this->m_PathToPlayer.empty())
    { return CCoord<>(0, 0); }

    // return (this->m_PathToPlayer[0].ToDouble() - this->GetLocationCell().ToDouble()) ;
    return m_DirectionsToPlayer[0].ToDouble();


    return CCoord<>(0, 0);

}

std::vector<CCoord<int>>
CEnemySmart::FindPathTo(const CBoard &board, CCoord<unsigned int> currentLocation, CCoord<unsigned int> targetLocation)
{
    std::vector<std::vector<bool>> map;
    map.resize(board.GetBoardSize().m_X);
    for (int i = 0; i < board.GetBoardSize().m_X; i++)
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
        }
    }


    std::vector<CCoord<int>> temp;
    std::vector<CCoord<int>> list;
    std::vector<CCoord<int>> tempDirections;
    std::vector<CCoord<int>> directions;

    FindPathToRec(map, currentLocation.m_X, currentLocation.m_Y, temp, list, tempDirections, directions,
                  targetLocation);

    if (!list.empty())
    {
        std::cout << "Location and path: " << std::endl;
        for (int i = 0; i < list.size(); i++)
        {
            if (i > 0)
            {
                //    std::cout << "location: " << list [i] << std::endl;
                //   std::cout << list[i] - list[i - 1] << std::endl;
                //  directions.push_back(list[i] - list[i - 1]);
            }
        }

        this->m_PathToPlayer = list;
        this->m_DirectionsToPlayer = directions;
    }

    return directions;
}

void CEnemySmart::FindPathToRec(std::vector<std::vector<bool>> &map, int i, int j, std::vector<CCoord<int>> &temp,
                                std::vector<CCoord<int>> &list, std::vector<CCoord<int>> &tempDirections,
                                std::vector<CCoord<int>> &directions, CCoord<unsigned int> targetLocation)
{
    if (i == targetLocation.m_X && j == targetLocation.m_Y)
    {
        list.clear();
        list.insert(list.end(), temp.begin(), temp.end());

        directions.clear();
        directions.insert(directions.end(), tempDirections.begin(), tempDirections.end());
        return;
    }

    std::vector<CCoord<int>> possibleDirections = {{-1, 0},
                                                   {1,  0},
                                                   {0,  -1},
                                                   {0,  1}};

    for (int k = 0; k < 4; k++)
    {
        int x = i + possibleDirections[k].m_X;
        int y = j + possibleDirections[k].m_Y;

        if (x >= 0 && y >= 0 && x <= map.size() - 1 && y <= map[0].size() - 1 && map[x][y] == true)
        {
            temp.push_back(CCoord<int>(x, y));
            tempDirections.push_back(possibleDirections[k]);

            bool prev = map[x][y];
            map[x][y] = false;

            FindPathToRec(map, x, y, temp, list, tempDirections, directions, targetLocation);

            map[x][y] = prev;
            temp.erase(temp.end() - 1);
            tempDirections.erase(tempDirections.end() - 1);
        }
    }
}

