/**
 * @author Jaroslav Fikar
*/

#include "CBlock.h"

void CBlock::Draw(CSDLInterface &interface, int cellSize, CCoord<> location, CCoord<> offset)
{
    // Create texture offset to target cell.
    CCoord<> textureOffset = CCoord<>((1 - this->m_TexturePack->GetTextureSize().m_X),
                                      (1 - this->m_TexturePack->GetTextureSize().m_Y));

    // Center texture position if required.
    if (this->m_TexturePack->IsCentered())
    { textureOffset /= 2; }

    unsigned int index = 0;

    // Setup final location and draw texture in right position.
    location = location + textureOffset + offset;
    interface.RenderTexture(this->m_TexturePack->GetTexture(ETextureType::TEXTURE_FRONT, &index),
                            CCoord<>(location.m_X * cellSize, location.m_Y * cellSize),
                            cellSize * this->m_TexturePack->GetTextureSize());
}
