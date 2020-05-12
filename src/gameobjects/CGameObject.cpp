/**
 * @author Jaroslav Fikar
 * 
*/

#include "CGameObject.h"
#include "../CBoard.h"

void CGameObject::Draw(CSDLInterface * interface,  int cellSize, CCoord location, CCoord offset) const
{
    location = location + offset;
    interface->RenderTexture(this->GetTexture(), CCoord(location.m_X * cellSize, location.m_Y * cellSize ), CCoord(cellSize, cellSize));
}
