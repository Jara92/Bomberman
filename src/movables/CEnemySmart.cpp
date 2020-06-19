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
    for (int i = 0; i < deltaTime; i++)
    {
        if (/*this->m_MovementMode == EEnemyMovementMode::ENEMY_MOVEMENT_MODE_RANDOM && */this->TurnRandom(board))
        { continue; }
        else if (this->GoForward(board))
        { continue; }
        else
        { this->GoRandom(board); }
    }
}

