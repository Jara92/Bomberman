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

    this->m_MovementModeTimer.Reset();
}

/*====================================================================================================================*/

void CEnemySmart::Move(const CBoard &board, int deltaTime)
{
    for (int i = 0; i < deltaTime; i++)
    {
        // Check for dangerous objects in front of this enemy.
        if (!this->DirectionIsSafe(board, this->m_Movement, this->m_SurveillanceDistance))
        {
           /* if (this->RunAway(board))
            { continue; }*/
          // this->m_MovementMode = EEnemyMovementMode::ENEMY_MOVEMENT_MODE_WALK_RANDOM;
        }

        if (this->GoForward(board))
        { continue; }
        else
        { this->GoRandom(board); }
       //this->TurnRandom(board);
    }
}

/*====================================================================================================================*/
bool CEnemySmart::RunAway(const CBoard &board)
{
    auto directions = this->GetPossibleMoveDirections(board);

    // Do nothing when there is no option.
    if (directions.empty())
    {
        std::cout << "directions empty" << std::endl;
        this->m_Movement = CCoord<>(0, 0);
        return false;
    } else
    {
        // Choose randomIndex direction and set new movement and texture type.
        unsigned int randomIndex = CRandom::Random(0, directions.size());

        // Do not move if the enemy is surrounded.
        if (this->m_Movement == directions[randomIndex] && directions.size() == 1)
        {

            std::cout << "directions equal" << std::endl;
            this->m_Movement = CCoord<>(0, 0);
            return false;
        }
            // Choose other direction if possible.
        else if (this->m_Movement == directions[randomIndex] && directions.size() > 1)
        {
            directions.erase(directions.begin() + randomIndex);
            randomIndex = CRandom::Random(0, directions.size());
        }

        this->m_Movement = directions[randomIndex];

        return this->GoForward(board);
    }
}

/*====================================================================================================================*/
bool CEnemySmart::FollowThePlayer(const CBoard &board)
{
    auto directions = this->GetPossibleMoveDirections(board);

    if (directions.size() <= 2)
    { return false; }

    if (!this->m_PersecutedPlayer)
    {
        unsigned int randomPlayer = CRandom::Random(0, board.m_Players.size());
        this->m_PersecutedPlayer = board.m_Players[randomPlayer];
    }

    CCoord<> targetLocation = this->m_PersecutedPlayer->GetLocation();

    this->m_Movement = this->FindBestWayToLocation(board, targetLocation);

    return this->GoForward(board);
}

/*====================================================================================================================*/
CCoord<> CEnemySmart::FindBestWayToLocation(const CBoard &board, CCoord<> location)
{
    auto directions = this->GetPossibleMoveDirections(board);

    // There is not avaible direction.
    if (directions.empty())
    {
        this->m_Movement = CCoord<>(0, 0);
        return CCoord<>(0, 0);
    }

    unsigned int bestDirectionIndex = 0;
    double bestDistance = 1000;

    for (std::size_t i = 0; i < directions.size(); i++)
    {
        // Calculate distance between this possible location and target location.
        double distance = (this->GetLocation() + directions[i]).CalcDistnance(location);

        if (distance < bestDistance)
        {
            bestDistance = distance;
            bestDirectionIndex = i;
        }
    }

    // Return the best.
    if (directions[bestDirectionIndex] == -1 * this->m_Movement)
    { return CCoord<>(0, 0); }
    return directions[bestDirectionIndex];
}

