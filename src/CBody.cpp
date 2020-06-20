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
    interface.RenderTexture(this->GetTexture(), cellSize * (location + textureOffset + offset),
                            cellSize * this->m_TexturePack->GetTextureSize());

    // Debug function - Render bounding box.
    if(interface.GetSettings().GetRenderBoundingBox())
    {
        CCoord<> center = ((CCoord<>(1, 1) - size) / 2);

        interface.SetRenderColor(0, 255, 0, 255);
        SDL_Rect rect{static_cast<int>((location.m_X + center.m_X + offset.m_X) * cellSize),
                      static_cast<int>((location.m_Y + center.m_Y + offset.m_Y) * cellSize),
                      static_cast<int>(cellSize * size.m_X ), static_cast<int>(cellSize * size.m_Y)};
        interface.RenderRectangle(&rect);
        interface.SetRenderColor(255, 0, 0, 255);
    }
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
