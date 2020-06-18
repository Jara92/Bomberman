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

    int actualMovementMode = static_cast<int>(this->m_MovementMode);
    int newMovementMode = 0;

    if (actualMovementMode < static_cast<int>(EEnemyMovementMode::ENEMY_MOVEMENT_MODE_NR_ITEMS) - 1)
    { newMovementMode = actualMovementMode + 1; }

    this->m_MovementMode = static_cast<EEnemyMovementMode >(newMovementMode);
    std::cout << "new mode " << newMovementMode << std::endl;
      this->m_MovementMode = EEnemyMovementMode::ENEMY_MOVEMENT_MODE_FOLLOW_THE_PLAYER;

    this->m_MovementModeTimer.Reset();
}

/*====================================================================================================================*/

void CEnemySmart::Move(const CBoard &board, int deltaTime)
{
    // this->m_MovementMode = EEnemyMovementMode::ENEMY_MOVEMENT_MODE_FOLLOW_THE_PLAYER; // FIXME REMOVE

    for (int i = 0; i < deltaTime; i++)
    {
        if (this->m_MovementMode == EEnemyMovementMode::ENEMY_MOVEMENT_MODE_FOLLOW_THE_PLAYER)
        {
            if (this->FollowThePlayer(board))
            { continue; }
        }
        continue;

        /* if (this->m_MovementMode == EEnemyMovementMode::ENEMY_MOVEMENT_MODE_WALK_RANDOM && this->TurnRandom(board))
         { continue; }
         else*/ if (this->GoForward(board))
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

    this->GoForward(board);

    if (this->m_Movement == CCoord<>(0, 0))
    { return false; }

    return true;
}

/*====================================================================================================================*/
CCoord<> CEnemySmart::FindWayToLocation(const CBoard &board, CCoord<unsigned int> location)
{
    if (this->m_PathToPlayer.empty())
    {
        this->FindPathToPlayer(board, this->GetLocationCell(), location);

        if (this->m_PathToPlayer.empty())
        {
            this->m_MovementMode = EEnemyMovementMode::ENEMY_MOVEMENT_MODE_WALK_RANDOM;
            return CCoord<>(0, 0);
        }
    }

    if (this->GetLocation().AlmostEqual(this->m_PathToPlayer[0].ToDouble(), this->m_Speed))
    {
        // Calibrate enemies location.
        this->m_Location = this->m_PathToPlayer[0].ToDouble();
        this->m_PathToPlayer.erase(this->m_PathToPlayer.begin());
        this->m_DirectionsToPlayer.erase(this->m_DirectionsToPlayer.begin());
    }

    if (this->m_PathToPlayer.empty())
    {
        this->m_MovementMode = EEnemyMovementMode::ENEMY_MOVEMENT_MODE_WALK_RANDOM;
        return CCoord<>(0, 0);
    }

    return m_DirectionsToPlayer[0];
}

bool
CEnemySmart::FindPathToPlayer(const CBoard &board, CCoord<unsigned int> currentLocation,
                              CCoord<unsigned int> targetLocation)
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

    std::vector<CCoord<unsigned int>> tempLocations;
    std::vector<CCoord<unsigned int>> locations;
    std::vector<CCoord<double>> tempDirections;
    std::vector<CCoord<double>> directions;

    FindPathToRec(map, currentLocation, tempLocations, locations, tempDirections, directions, targetLocation);

    if (!locations.empty())
    {
        this->m_PathToPlayer = locations;
        this->m_DirectionsToPlayer = directions;

        this->m_Movement = this->m_DirectionsToPlayer[0];

        return true;
    }

    return false;
}

void CEnemySmart::FindPathToRec(std::vector<std::vector<bool>> &map, CCoord<unsigned int> location,
                                std::vector<CCoord<unsigned int>> &tempLocations,
                                std::vector<CCoord<unsigned int>> &locations,
                                std::vector<CCoord<double>> &tempDirections, std::vector<CCoord<double>> &directions,
                                CCoord<unsigned int> targetLocation)
{
    // If I found my location i save every move step.
    if (location == targetLocation)
    {
        locations.clear();
        locations.insert(locations.end(), tempLocations.begin(), tempLocations.end());

        directions.clear();
        directions.insert(directions.end(), tempDirections.begin(), tempDirections.end());
        return;
    }

    std::vector<CCoord<int>> possibleDirections = {{-1, 0},
                                                   {1,  0},
                                                   {0,  -1},
                                                   {0,  1}};

    for (int i = 0; i < possibleDirections.size(); i++)
    {
        CCoord<unsigned int> newLocation = CCoord<unsigned int>(location.m_X + possibleDirections[i].m_X,
                                                                location.m_Y + possibleDirections[i].m_Y);

        if (newLocation.m_X <= map.size() - 1 && newLocation.m_Y <= map[0].size() - 1 &&
            map[newLocation.m_X][newLocation.m_Y] == true)
        {
            tempLocations.push_back(newLocation);
            tempDirections.push_back(possibleDirections[i].ToDouble());

            bool prev = map[newLocation.m_X][newLocation.m_Y];
            map[newLocation.m_X][newLocation.m_Y] = false;

            FindPathToRec(map, newLocation, tempLocations, locations, tempDirections, directions,
                          targetLocation);

            map[newLocation.m_X][newLocation.m_Y] = prev;
            tempLocations.erase(tempLocations.end() - 1);
            tempDirections.erase(tempDirections.end() - 1);
        }
    }
}

