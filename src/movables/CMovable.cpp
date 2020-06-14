/**
 * @author Jaroslav Fikar
*/

#include "CMovable.h"
#include "../CBoard.h"

/*====================================================================================================================*/
bool CMovable::CellIsFree(CBoard &board, CCoord<> location) const
{
    // All player corners must be passable - Look deltaTime * oneStep forward.
    double correction = (1 - this->m_Speed);

    if (!board.IsPassable(CCoord<unsigned int>(location.m_X, location.m_Y), *this) ||
        !board.IsPassable(CCoord<unsigned int>(location.m_X + correction, location.m_Y), *this) ||
        !board.IsPassable(CCoord<unsigned int>(location.m_X, location.m_Y + correction), *this) ||
        !board.IsPassable(CCoord<unsigned int>(location.m_X + correction, location.m_Y + correction),
                          *this))
    { return false; }

    return true;
}

/*====================================================================================================================*/
void CMovable::Reset(CBoard &board)
{
    this->m_Body.Reset();
    this->m_Location = this->m_StartingLocation;
    this->m_IsAlive = true;
}

