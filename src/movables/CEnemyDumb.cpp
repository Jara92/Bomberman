/**
 * @author Jaroslav Fikar
*/

#include "CEnemyDumb.h"
#include "../CBoard.h"

void CEnemyDumb::Update(CBoard &board, int deltaTime)
{
    CEnemy::Update(board, deltaTime);
    this->m_RandomMovementTimer.Tick(deltaTime);

    // Move when the enemy is alive.
    if (this->m_IsAlive)
    {
        CCoord<> oldLocation = this->m_Location;

        this->Move(board, deltaTime);

        this->UpdateTextureType(oldLocation);
    }
}

/*====================================================================================================================*/
void CEnemyDumb::Move(const CBoard &board, int deltaTime)
{
    for (int i = 0; i < deltaTime; i++)
    {
        // Check for dangerous objects in front of this enemy.
        if (!this->DirectionIsSafe(board, this->m_Movement, this->m_SurveillanceDistance))
        {
            if (this->RunAway(board))
            { continue; }
        }

        // Move
        if (this->m_MovementMode == EEnemyMovementMode::ENEMY_MOVEMENT_MODE_WALK_RANDOM)
        {
            if (this->TurnRandom(board))
            { continue; }
        }

        if (this->GoForward(board))
        { continue; }
        else
        { this->GoRandom(board); }
    }
}

/*====================================================================================================================*/
bool CEnemyDumb::TurnRandom(const CBoard &board)
{
    auto directions = this->GetPossibleMoveDirections(board);

    if (directions.size() > 2)
    {
        // Choose randomIndex direction and set new movement and texture type.
        unsigned int randomIndex = CRandom::Random(0, directions.size());

        // Remove forward and backward direction.
        while (!directions.empty() && (directions[randomIndex] == this->m_Movement ||
                                       directions[randomIndex] == -1 * this->m_Movement))
        {
            directions.erase(directions.begin() + randomIndex);
            randomIndex = CRandom::Random(0, directions.size());
        }

        if (!directions.empty())
        {
            this->m_Movement = directions[randomIndex];

            bool move = this->GoForward(board);

            if (move)
            {
                this->m_RandomMovementTimer.Reset();
                this->UpdateMovementMode();
                return move;
            }
        }
    }

    return this->GoForward(board);
}

/*====================================================================================================================*/
void CEnemyDumb::UpdateMovementMode()
{
    if (this->m_MovementMode == EEnemyMovementMode::ENEMY_MOVEMENT_MODE_WALK_RANDOM)
    { this->m_MovementMode = EEnemyMovementMode::ENEMY_MOVEMENT_MODE_WALK_FORWARD; }
    else if (this->m_MovementMode == EEnemyMovementMode::ENEMY_MOVEMENT_MODE_WALK_FORWARD)
    { this->m_MovementMode = EEnemyMovementMode::ENEMY_MOVEMENT_MODE_WALK_RANDOM; }
}
