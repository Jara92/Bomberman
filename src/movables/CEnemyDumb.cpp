/**
 * @author Jaroslav Fikar
*/

#include "CEnemyDumb.h"
#include "../CBoard.h"

void CEnemyDumb::Update(CBoard &board, int deltaTime)
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
void CEnemyDumb::Move(const CBoard &board, int deltaTime)
{
    for (int i = 0; i < deltaTime; i++)
    {
        // Go forward until the way is blocked.
        if (this->GoForward(board))
        { continue; }
        else
        { this->GoRandom(board); }
    }
}
