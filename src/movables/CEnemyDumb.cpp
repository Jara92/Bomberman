/**
 * @author Jaroslav Fikar
 * 
*/


#include "CEnemyDumb.h"
#include "../CBoard.h"

void CEnemyDumb::Update(CBoard &board, int deltaTime)
{
    CEnemy::Update(board, deltaTime);
    this->m_DeadTimer.Tick(deltaTime);

    CCoord<> oldLocation = this->m_Location;

    if (this->m_IsAlive)
    {
        this->WalkAround(board, deltaTime);
    }

    this->UpdateTextureType(oldLocation);
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
            this->m_DeadTimer.Run(CEnemy::ENEMY_DESTROY_DELAY, [=](void)
            {
                this->m_IsDestroyed = true;
            });

            return score;
        }
    }

    return 0;
}

/*====================================================================================================================*/
void CEnemyDumb::WalkAround(CBoard &board, int deltaTime)
{
    // Move deltaTime times.
    for (int i = 0; i < deltaTime; i++)
    {
        // Save old location and move.
        CCoord<> oldLocation = this->m_Location;
        this->m_Location += (this->m_Movement * this->m_Speed);

        // If enemy stands still or new location is not free.
        if (this->m_Movement == CCoord<>(0, 0) || !this->CellIsFree(board, this->m_Location))
        {
            // Recover location and get avaible directions to go.
            this->m_Location = oldLocation;
            auto directions = this->GetPossibleMoveDirections(board);

            // Stand still if there is no direction to go.
            if (directions.empty())
            {
                this->m_Movement = CCoord<>(0, 0);
                this->m_Body.SetActualTextureType(ETextureType::TEXTURE_FRONT);
            }
                // Go to random direction.
            else
            {
                unsigned seed = std::chrono::system_clock::now().time_since_epoch().count() * rand();
                std::default_random_engine randomEngine(seed);

                // Choose random direction and set new movemnt and texture type.
                unsigned int random = randomEngine() % directions.size();
                this->m_Movement = directions[random];

                this->m_Location += (this->m_Movement * this->m_Speed);
            }
        }
    }
}
