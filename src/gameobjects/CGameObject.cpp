/**
 * @author Jaroslav Fikar
 * 
*/

#include "CGameObject.h"
#include "../CBoard.h"

void CGameObject::Draw(CSDLInterface *interface, int cellSize, CCoord location, CCoord offset) const
{
    // Create texture offset to target cell.
    CCoord textureOffset = CCoord((1 - this->m_TexturePack->GetTextureSize().m_X),
                                  (1 - this->m_TexturePack->GetTextureSize().m_Y));

    // Center texture position if required.
    if (this->m_TexturePack->IsCentered())
    {
        textureOffset /= 2;
    }

    // Setup final location and draw texture in right position.
    location = location + textureOffset + offset;
    interface->RenderTexture(this->GetTexture(), CCoord(location.m_X * cellSize, location.m_Y * cellSize),
                             cellSize * this->m_TexturePack->GetTextureSize());
}

/*====================================================================================================================*/
SDL_Texture *CGameObject::GetTexture() const
{
    SDL_Texture *texture = this->m_TexturePack.get()->GetTexture(this->m_ActualTexture, &(this->m_AnimationIndex));

    return texture;
}

