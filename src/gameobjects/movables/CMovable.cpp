/**
 * @author Jaroslav Fikar
 * 
*/


#include "CMovable.h"
#include "../../CBoard.h"

/*====================================================================================================================*/
bool CMovable::CellIsFree(CBoard &board, int deltaTime, CCoord<> location) const
{
    // All player corners must be passable - Look deltaTime * oneStep forward.
    double correction = (1 - deltaTime * this->m_Speed);

    if (!board.IsPassable(CCoord<unsigned int>(location.m_X, location.m_Y), this) ||
        !board.IsPassable(CCoord<unsigned int>(location.m_X + correction, location.m_Y), this) ||
        !board.IsPassable(CCoord<unsigned int>(location.m_X, location.m_Y + correction), this) ||
        !board.IsPassable(CCoord<unsigned int>(location.m_X + correction, location.m_Y + correction),
                           this))
    { return false; }

    return true;
}

/*====================================================================================================================*/
void CMovable::Animate(int deltaTime)
{
    // Animate object when moving
    if (this->m_Movement != CCoord<>(0, 0))
    { CGameObject::Animate(deltaTime); }
}

/*====================================================================================================================*/
void CMovable::Reset(CBoard & board)
{
    CGameObject::Reset(board);
    this->m_Location = this->m_StartingLocation;
    this->m_AnimationIndex = this->m_AnimationTimer = 0;
    this->m_ActualTexture = ETextureType::TEXTURE_FRONT;
    this->m_IsAlive = true;
}

