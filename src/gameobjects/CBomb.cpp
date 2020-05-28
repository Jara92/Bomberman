/**
 * @author Jaroslav Fikar
 * 
*/


#include "CBomb.h"


void CBomb::Update(CBoard *board, int deltaTime)
{
    this->m_ExplosionCounter += deltaTime;

    if (this->m_ExplosionCounter >= this->m_ExplosionDelay)
    {
        this->m_ExplosionCounter = 0;
        this->m_ExplosionDelay = 0;

        this->Detonate(board);
    }
}

/*====================================================================================================================*/
void CBomb::Detonate(CBoard *board)
{
    if (this->m_ExplosionDelay == 0)
    {
        //board.CreateExplosion()
    }
}
