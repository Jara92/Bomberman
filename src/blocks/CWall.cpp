/**
 * @author Jaroslav Fikar
*/

#include "CWall.h"

bool CWall::TryDestroy(unsigned int distance)
{
    if (this->m_IsDestructible)
    {
        if (this->m_Collectible)
        { this->m_Collectible->MakeVisible(); }

        this->m_IsAlive = false;

        return true;
    }

    return false;
}

/*====================================================================================================================*/
bool CWall::IsPassable(CCoord<unsigned int> thisLocation, const CMovable &movable) const
{
    // Destructible walls are passable for movables which are able to pass walls.
    if (movable.GetWallPass() && this->m_IsDestructible)
    { return true; }

    return false;
}
