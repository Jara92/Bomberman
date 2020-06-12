/**
 * @author Jaroslav Fikar
 * 
*/


#include "CEnemyDump.h"
#include "../../CBoard.h"

void CEnemyDump::Update(CBoard *board, int deltaTime)
{
   // CEnemy::Update(board, deltaTime);

    auto directions = this->GetPossibleMoveDirections(board);

    CCoord<> oldLocation = this->m_Location;

    this->m_Location += (this->m_Direction * deltaTime * this->m_Speed);

    if(this->m_Direction == CCoord<>(0,0) || !this->CellIsFree(board, this->m_Location))
    {
        this->m_Location = oldLocation;
        if(directions.empty())
        {
            this->m_Direction = CCoord<>(0,0);
            this->m_ActualTexture = ETextureType ::TEXTURE_FRONT;
        }
        else
        {
            if(directions.size() > 2)
            {
                this->m_Direction = directions[2].second;
                this->m_ActualTexture = directions[2].first;
            }
            else
            {
                this->m_Direction = directions[0].second;
                this->m_ActualTexture = directions[0].first;
            }
            this->m_Location += (this->m_Direction * deltaTime * this->m_Speed);
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
