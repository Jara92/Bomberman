/**
 * @author Jaroslav Fikar
 * 
*/


#include "CMovable.h"

void CMovable::Draw(CSDLInterface *interface, int cellSize, CCoord offset) const
{
    this->Draw(interface, cellSize, this->m_Location, offset);
}
