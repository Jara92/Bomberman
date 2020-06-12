/**
 * @author Jaroslav Fikar
 * 
*/


#include "CEnemyDump.h"

void CEnemyDump::Update(CBoard *board, int deltaTime)
{
    // TODO Dump AI staff...
//    this->m_Location += (this->GetPossibleMoveDirections(board)[0] * deltaTime);
    // zde budou volány metody hloupého nepřítele

    //CEnemy::Update(board, deltaTime);
    // Todo Smart enemy AI staff
    // Zde budou volány metody chytrého nepřítele
   /* CCoord<> newLocation = this->m_Location + (m_Direction * deltaTime * this->m_Speed);
    if (this->m_Direction == CCoord<>(0, 0) || !this->CellIsFree(board, newLocation))
    {
        auto directions = this->GetPossibleMoveDirections(board);

        if (!directions.empty())
        {
            m_Direction = directions[0].second;
            this->m_ActualTexture = directions[0].first;
         //   std::cout << "way ok" << std::endl;

        }
        else
        {
           // m_Direction = this->FindWayOut(board);
           // std::cout << "find way out" << std::endl;
        }

        newLocation = this->m_Location + (m_Direction * deltaTime * this->m_Speed);
    }

    this->m_Location = newLocation;*/

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
