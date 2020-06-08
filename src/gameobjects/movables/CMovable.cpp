/**
 * @author Jaroslav Fikar
 * 
*/


#include "CMovable.h"

/*====================================================================================================================*/
void CMovable::Animate(int deltaTime)
{
    // Animate object when moving
    if (this->m_VerticalMovingDirection != EDirection::DIRECTION_NONE ||
        this->m_HorizontalMovingDirection != EDirection::DIRECTION_NONE)
    {CGameObject::Animate(deltaTime);    }
}

/*====================================================================================================================*/
void CMovable::Reset()
{
    this->m_Location = this->m_StartingLocation;
    this->m_AnimationIndex = 0;
    this->m_AnimationTimer = 0;

    this->m_IsAlive = true;
}

