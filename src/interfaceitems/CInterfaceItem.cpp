/**
 * @author Jaroslav Fikar
 * 
*/


#include "CInterfaceItem.h"

bool CInterfaceItem::MouseCollision(CCoord<unsigned int> mouseLocation) const
{
    if (mouseLocation.m_X >= this->m_Location.m_X && mouseLocation.m_X <= this->m_Location.m_X + this->m_Size.m_X &&
        mouseLocation.m_Y >= this->m_Location.m_Y && mouseLocation.m_Y <= this->m_Location.m_Y + this->m_Size.m_Y)
    { return true; }
    else
    { return false; }
}
