/**
 * @author Jaroslav Fikar
 * 
*/


#include "CMovable.h"
#include "../../CBoard.h"

/*====================================================================================================================*/
bool CMovable::CellIsFree(CBoard *board, CCoord<> location) const
{
    // All player corners must be passable - but we need to correct cell size to check right cells.
    double correction = (1 - this->m_Speed);

    if (!board->IsPassable(CCoord<unsigned int>(location.m_X, location.m_Y), this) ||
        !board->IsPassable(CCoord<unsigned int>(location.m_X + correction, location.m_Y), this) ||
        !board->IsPassable(CCoord<unsigned int>(location.m_X, location.m_Y + correction), this) ||
        !board->IsPassable(CCoord<unsigned int>(location.m_X + correction, location.m_Y + correction),
                           this))
    { return false; }

    return true;
}

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
    this->m_AnimationIndex = this->m_AnimationTimer = 0;
    this->m_ActualTexture = ETextureType ::TEXTURE_FRONT;
    this->m_IsAlive = true;
}

