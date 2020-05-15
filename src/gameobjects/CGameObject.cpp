/**
 * @author Jaroslav Fikar
 * 
*/

#include "CGameObject.h"
#include "../CBoard.h"

void CGameObject::Draw(CSDLInterface *interface, int cellSize, CCoord location, CCoord offset) const
{
    location = location + offset - this->m_TexturePack->GetTextureSize() + CCoord(1, 1);
    interface->RenderTexture(this->GetTexture(), CCoord(location.m_X * cellSize, location.m_Y * cellSize),
                             cellSize * this->m_TexturePack->GetTextureSize());
}

