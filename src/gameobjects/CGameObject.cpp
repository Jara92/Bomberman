/**
 * @author Jaroslav Fikar
 * 
*/

#include "CGameObject.h"
#include "../CBoard.h"

void CGameObject::Draw(CSDLInterface *interface, int cellSize, CCoord location, CCoord offset) const
{
    // Calculate texture location.
    location = location + offset - this->m_TexturePack->GetTextureSize() + CCoord(1, 1);

    interface->RenderTexture(this->GetTexture(), CCoord(location.m_X * cellSize, location.m_Y * cellSize),
                             cellSize * this->m_TexturePack->GetTextureSize());
}
/*====================================================================================================================*/
SDL_Texture *CGameObject::GetTexture() const
{
    SDL_Texture * texture = this->m_TexturePack.get()->GetTexture(this->m_ActualTexture, &(this->m_AnimationIndex));
  //  this->m_AnimationIndex++;

    return texture;
}

