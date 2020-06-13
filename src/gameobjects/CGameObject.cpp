/**
 * @author Jaroslav Fikar
 * 
*/

#include "CGameObject.h"
#include "../CBoard.h"

void CGameObject::Draw(CSDLInterface &interface, int cellSize, CCoord<> location, CCoord<> offset) const
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

    // FIXME debug
  /*    CCoord<> center = ((CCoord<>(1, 1) - this->m_Size) / 2);


    interface->SetRenderColor(0, 255, 0, 255);
    SDL_Rect rect{static_cast<int>((this->m_Location.m_X + center.m_X + offset.m_X) * cellSize),
                  static_cast<int>((this->m_Location.m_Y + center.m_Y + offset.m_Y) * cellSize),
                  static_cast<int>(cellSize * this->GetSize().m_X ), static_cast<int>(cellSize * this->GetSize().m_Y)};
    interface->RenderRectangle(&rect);
    interface->SetRenderColor(255, 0, 0, 255);*/

}

/*====================================================================================================================*/
SDL_Texture *CGameObject::GetTexture() const
{
    SDL_Texture *texture = this->m_TexturePack.get()->GetTexture(this->m_ActualTexture, &(this->m_AnimationIndex));

    return texture;
}

/*====================================================================================================================*/

bool CGameObject::IsColliding(const CGameObject *other) const
{
    double cellSize = 1;
    CCoord<> a = this->GetLocation() + ((CCoord<>(1, 1) - this->m_Size) / 2);
    CCoord<> b = other->GetLocation() + ((CCoord<>(1, 1) - other->m_Size) / 2);

    if (a.m_X < b.m_X + /*b.width*/std::min(other->GetSize().m_X, cellSize) &&
        a.m_X + /*a.width*/std::min(this->GetSize().m_X, cellSize) > b.m_X &&
        a.m_Y < b.m_Y + /*b.height*/std::min(other->GetSize().m_Y, cellSize) &&
        a.m_Y + /*a.height*/std::min(this->GetSize().m_Y, cellSize) > b.m_Y)
    { return true; }

    return false;
}

