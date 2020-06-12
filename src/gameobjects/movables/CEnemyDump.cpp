/**
 * @author Jaroslav Fikar
 * 
*/


#include "CEnemyDump.h"
#include "../../CBoard.h"

void CEnemyDump::Update(CBoard *board, int deltaTime)
{
    CEnemy::Update(board, deltaTime);

    auto directions = this->GetPossibleMoveDirections(board, deltaTime);

    CCoord<> oldLocation = this->m_Location;

    this->m_Location += (this->m_Movement * deltaTime * this->m_Speed);

    if(this->m_Movement == CCoord<>(0,0) || !this->CellIsFree(board, deltaTime, this->m_Location))
    {
        this->m_Location = oldLocation;
        if(directions.empty())
        {
            this->m_Movement = CCoord<>(0,0);
            this->m_ActualTexture = ETextureType ::TEXTURE_FRONT;
        }
        else
        {
            std::size_t random = rand() % directions.size();
            this->m_Movement = directions[random].second;
            this->m_ActualTexture = directions[random].first;

            this->m_Location += (this->m_Movement * deltaTime * this->m_Speed);
        }
    }
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

void CEnemyDump::WalkAround()
{

}
