/**
 * @author Jaroslav Fikar
 * 
*/


#include "CFire.h"
#include "../CBoard.h"

void CFire::Update(CBoard &board, int deltaTime)
{
    CGameObject::Update(board, deltaTime);

    // Update duration counter and destroy fire.
    this->m_DurationCounter += deltaTime;

    // Destroy this fire
    if (this->m_DurationCounter > this->m_Duration)
    { board.DestroyExplosion(this); }
}
