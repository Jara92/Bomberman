/**
 * @author Jaroslav Fikar
 * 
*/


#include "CMovable.h"
#include "../../CBoard.h"

/*====================================================================================================================*/
bool CMovable::CellIsFree(CBoard &board, int deltaTime, CCoord<> location) const
{
    // All player corners must be passable - Look deltaTime * oneStep forward.
    double correction = (1 - deltaTime * this->m_Speed);

    if (!board.IsPassable(CCoord<unsigned int>(location.m_X, location.m_Y), this) ||
        !board.IsPassable(CCoord<unsigned int>(location.m_X + correction, location.m_Y), this) ||
        !board.IsPassable(CCoord<unsigned int>(location.m_X, location.m_Y + correction), this) ||
        !board.IsPassable(CCoord<unsigned int>(location.m_X + correction, location.m_Y + correction),
                          this))
    { return false; }

    return true;
}

/*====================================================================================================================*/
void CMovable::Animate(int deltaTime)
{
    // Animate object when moving
    if (this->m_Movement != CCoord<>(0, 0))
    {
        this->m_AnimationTimer += deltaTime;
        if (this->m_AnimationTimer >= this->m_AnimationUpdateInterval)
        {
            this->m_AnimationIndex++;
            this->m_AnimationTimer = 0;
        }
    }
}

/*====================================================================================================================*/
void CMovable::Reset(CBoard &board)
{
    this->m_Location = this->m_StartingLocation;
    this->m_AnimationIndex = this->m_AnimationTimer = 0;
    this->m_ActualTexture = ETextureType::TEXTURE_FRONT;
    this->m_IsAlive = true;
}

/*====================================================================================================================*/
bool CMovable::IsColliding(const CMovable *other) const
{
    double cellSize = 1;
    CCoord<> a = this->GetLocation() + ((CCoord<>(1, 1) - this->m_Size) / 2);
    CCoord<> b = other->GetLocation() + ((CCoord<>(1, 1) - other->m_Size) / 2);

    if (a.m_X < b.m_X + std::min(other->GetSize().m_X, cellSize) &&
        a.m_X + std::min(this->GetSize().m_X, cellSize) > b.m_X &&
        a.m_Y < b.m_Y + std::min(other->GetSize().m_Y, cellSize) &&
        a.m_Y + std::min(this->GetSize().m_Y, cellSize) > b.m_Y)
    { return true; }

    return false;
}

/*====================================================================================================================*/
void CMovable::Draw(CSDLInterface &interface, int cellSize, CCoord<> location, CCoord<> offset) const
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

