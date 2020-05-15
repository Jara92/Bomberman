/**
 * @author Jaroslav Fikar
 * 
*/


#include "CEnemyDump.h"

void CEnemyDump::Update(CBoard *board, int deltaTime)
{
    // TODO Dump AI staff...
    // zde budou volány metody hloupého nepřítele
}

/*====================================================================================================================*/
int CEnemyDump::TryKill(unsigned int distance)
{
    (void)(distance);
    this->m_Lives--;

    // Check lives of the monster
    if(this->m_Lives <= 0)
    {
        this->m_IsAlive = false;
        int score = this->m_Score;
        // Set score to 0 to make sure player doesn't get it more than once
        this->m_Score = 0;

        return score;
    }

    return 0;
}
