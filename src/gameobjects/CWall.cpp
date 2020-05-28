/**
 * @author Jaroslav Fikar
 * 
*/


#include "CWall.h"

bool CWall::TryDestroy(int distance)
{
    if(this->m_IsDestructible)
    {
        if(this->m_Collectible)
        {
            this->m_Collectible->MakeVisible();
        }
        /* There is no MEMLEAK. Another pointer to this object is in the Board.
        * This pointer is saved to call MakeVisible() method when the wall is being destroyed.
        * Destroyed object has no reason to have this pointer.
        */
        this->m_Collectible = nullptr;

        this->m_IsAlive = false;

        return true;
    }

    return false;
}
