/**
 * @author Jaroslav Fikar
 * 
*/


#include "CEnemyDump.h"
#include "../CBoard.h"

void CEnemyDump::Update(CBoard &board, int deltaTime)
{
    CEnemy::Update(board, deltaTime);

    this->WalkAround(board, deltaTime);
}

/*====================================================================================================================*/
int CEnemyDump::TryKill(unsigned int distance)
{
    this->m_Lives--;

    // Check lives of the monster
    if (this->m_Lives <= 0)
    {
        this->m_IsAlive = false;
        int score = this->m_Score;
        // Set score to 0 to make sure player doesn't get it more than once
        this->m_Score = 0;

        return score;
    }

    return 0;
}
/*====================================================================================================================*/
void CEnemyDump::WalkAround(CBoard & board, int deltaTime)
{
    // Save old location and move.
    CCoord<> oldLocation = this->m_Location;
    this->m_Location += (this->m_Movement * deltaTime * this->m_Speed);

    // If enemy stands still or new location is not free.
    if(this->m_Movement == CCoord<>(0,0) || !this->CellIsFree(board, deltaTime, this->m_Location))
    {
        // Recover location and get avaible directions to go.
        this->m_Location = oldLocation;
        auto directions = this->GetPossibleMoveDirections(board, deltaTime);

        // Stand still if there is no direction to go.
        if(directions.empty())
        {
            this->m_Movement = CCoord<>(0,0);
            this->m_ActualTexture = ETextureType ::TEXTURE_FRONT;
        }
            // Go to random direction.
        else
        {
            unsigned seed = std::chrono::system_clock::now().time_since_epoch().count() * rand();
            std::default_random_engine randomEngine(seed);

            // Choose random direction and set new movemnt and texture type.
            unsigned int random = randomEngine() % directions.size();
            this->m_Movement = directions[random].second;
            this->m_ActualTexture = directions[random].first;

            this->m_Location += (this->m_Movement * deltaTime * this->m_Speed);
        }
    }
}
