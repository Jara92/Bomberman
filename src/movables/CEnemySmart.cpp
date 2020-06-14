/**
 * @author Jaroslav Fikar
 * 
*/


#include "CEnemySmart.h"

void CEnemySmart::Update(CBoard &board, int deltaTime)
{
    CEnemy::Update(board, deltaTime);
}
/*====================================================================================================================*/
unsigned int CEnemySmart::TryKill(unsigned int distance)
{
    // Todo Smart enemy staff
    return 0;
}
