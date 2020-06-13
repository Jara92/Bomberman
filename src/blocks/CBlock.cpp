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

    // Setup final location and draw texture in right position.
    location = location + textureOffset + offset;
    interface.RenderTexture(this->GetTexture(), CCoord<>(location.m_X * cellSize, location.m_Y * cellSize),
                            cellSize * this->m_TexturePack->GetTextureSize());
}

bool CBlock::IsColliding(CCoord<unsigned int> thisLocation, const CGameObject &other) const
{
    double cellSize = 1;
    CCoord<> a = thisLocation.ToDouble() + ((CCoord<>(1, 1) - this->m_Size) / 2);
    CCoord<> b = other.GetLocation() + ((CCoord<>(1, 1) - other.GetSize()) / 2);

    if (a.m_X < b.m_X + std::min(other.GetSize().m_X, cellSize) &&
        a.m_X + std::min(this->m_Size.m_X, cellSize) > b.m_X &&
        a.m_Y < b.m_Y + std::min(other.GetSize().m_Y, cellSize) &&
        a.m_Y + std::min(this->m_Size.m_Y, cellSize) > b.m_Y)
    { return true; }

    return false;
}

bool CBlock::IsPassable(CCoord<unsigned int> thisLocation, const CMovable &movable) const
{
    if(this->IsColliding(thisLocation, movable))
    {return this->m_IsPassable;}

    return true;
}
