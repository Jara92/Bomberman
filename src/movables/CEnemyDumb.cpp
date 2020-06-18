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
void CEnemyDumb::UpdateMovementMode()
{
    if (this->m_MovementMode == EEnemyMovementMode::ENEMY_MOVEMENT_MODE_WALK_RANDOM)
    { this->m_MovementMode = EEnemyMovementMode::ENEMY_MOVEMENT_MODE_WALK_FORWARD; }
    else if (this->m_MovementMode == EEnemyMovementMode::ENEMY_MOVEMENT_MODE_WALK_FORWARD)
    { this->m_MovementMode = EEnemyMovementMode::ENEMY_MOVEMENT_MODE_WALK_RANDOM; }
}
