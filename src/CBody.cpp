/**
 * @author Jaroslav Fikar
 * 
*/


#include "CBody.h"

void CBody::Draw(CSDLInterface &interface, int cellSize, CCoord<> location, CCoord<> size, CCoord<> offset) const
{
    // Create texture offset to target cell.
    CCoord<> textureOffset = CCoord<>((1 - this->m_TexturePack->GetTextureSize().m_X),
                                      (1 - this->m_TexturePack->GetTextureSize().m_Y));

    // Center texture position if required.
    if (this->m_TexturePack->IsCentered())
    { textureOffset /= 2; }

    // Setup final location and draw texture in right position.
    location = location + textureOffset + offset;
    interface.RenderTexture(this->GetTexture(), CCoord<>(location.m_X * cellSize, location.m_Y * cellSize),
                            cellSize * this->m_TexturePack->GetTextureSize());
}

/*====================================================================================================================*/
bool
CBody::IsColliding(CCoord<> aLocation, CCoord<> aSize, CCoord<> bLocation, CCoord<> bSize) const
{
    double cellSize = 1;
    CCoord<> a = aLocation + ((CCoord<>(1, 1) - aSize) / 2);
    CCoord<> b = bLocation + ((CCoord<>(1, 1) - bSize) / 2);

    if (a.m_X < b.m_X + std::min(bSize.m_X, cellSize) &&
        a.m_X + std::min(aSize.m_X, cellSize) > b.m_X &&
        a.m_Y < b.m_Y + std::min(bSize.m_Y, cellSize) &&
        a.m_Y + std::min(aSize.m_Y, cellSize) > b.m_Y)
    { return true; }

    return false;
}
