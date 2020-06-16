/**
 * @author Jaroslav Fikar
*/

#include "CEnemyDumb.h"
#include "../CBoard.h"

void CEnemyDumb::Update(CBoard &board, int deltaTime)
{
    CEnemy::Update(board, deltaTime);
    this->m_DestroyTimer.Tick(deltaTime);

    // Move when the enemy is alive.
    if (this->m_IsAlive)
    {
        CCoord<> oldLocation = this->m_Location;

        this->Move(board, deltaTime);

        this->UpdateTextureType(oldLocation);
    }
}

/*====================================================================================================================*/
unsigned int CEnemyDumb::TryKill(unsigned int distance)
{
    if (this->m_IsAlive)
    {
        this->m_Lives--;

        // Check lives of the monster
        if (this->m_Lives <= 0)
        {
            this->m_IsAlive = false;
            this->m_Movement = CCoord<>(0, 0);

            int score = this->m_Score;
            // Set score to 0 to make sure player doesn't get it more than once
            this->m_Score = 0;

            // Destroy the object with a delay.
            this->m_DestroyTimer.Run(CEnemy::ENEMY_DESTROY_DELAY, [=](void)
            {
                this->m_IsDestroyed = true;
            });

            return score;
        }
    }

    return 0;
}

/*====================================================================================================================*/
void CEnemyDumb::Move(const CBoard &board, int deltaTime)
{
    for (int i = 0; i < deltaTime; i++)
    {
        // Check for dangerous objects in front of this enemy.
        if (!this->DirectionIsSafe(board, this->m_SurveillanceDistance))
        { this->RunAway(board, deltaTime); }

        // Move
        if (this->GoForward(board))
        { continue; }
        else
        { this->GoRandom(board); }
    }
}
