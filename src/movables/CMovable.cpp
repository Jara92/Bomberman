/**
 * @author Jaroslav Fikar
*/

#include "CMovable.h"
#include "../CBoard.h"

/*====================================================================================================================*/
bool CMovable::LocationIsFree(const CBoard &board) const
{
    // All player corners must be passable - Look deltaTime * oneStep forward.
    double correction = (1 - this->m_Speed);

    if (!board.IsPassable(CCoord<unsigned int>(this->m_Location.m_X, this->m_Location.m_Y), *this) ||
        !board.IsPassable(CCoord<unsigned int>(this->m_Location.m_X + correction, this->m_Location.m_Y), *this) ||
        !board.IsPassable(CCoord<unsigned int>(this->m_Location.m_X, this->m_Location.m_Y + correction), *this) ||
        !board.IsPassable(CCoord<unsigned int>(this->m_Location.m_X + correction, this->m_Location.m_Y + correction),
                          *this))
    { return false; }

    return true;
}

/*====================================================================================================================*/
void CMovable::NextLevel(CBoard &board, bool clearLevelObjects)
{
    this->m_Body.Reset();
    this->m_Location = this->m_StartingLocation;
    this->m_IsAlive = true;
}

void CMovable::UpdateTextureByMovement(CCoord<> diff)
{
    // Set right texture by movement vector.
    if (diff.m_X < -this->m_Speed)
    { this->m_Body.SetActualTextureType(ETextureType::TEXTURE_RIGHT); }
    else if (diff.m_X > this->m_Speed)
    { this->m_Body.SetActualTextureType(ETextureType::TEXTURE_LEFT); }
    else if (diff.m_Y < -this->m_Speed)
    { this->m_Body.SetActualTextureType(ETextureType::TEXTURE_FRONT); }
    else if (diff.m_Y > this->m_Speed)
    { this->m_Body.SetActualTextureType(ETextureType::TEXTURE_BACK); }
}




