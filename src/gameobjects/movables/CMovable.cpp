/**
 * @author Jaroslav Fikar
 * 
*/


#include "CMovable.h"

void CMovable::Draw(CSDLInterface *interface, int cellSize, CCoord offset) const
{
    this->Draw(interface, cellSize, this->m_Location, offset);

   /* // TODO render debug square
    interface->SetRenderColor(0, 255, 0, 255);
    SDL_Rect rect{static_cast<int>(this->m_Location.m_X * cellSize), static_cast<int>(this->m_Location.m_Y * cellSize),
                  static_cast<int>(1 * cellSize), static_cast<int>(1 * cellSize)};
    interface->RenderRectangle(&rect);
    interface->SetRenderColor(255, 0, 0, 255);*/
}

/*====================================================================================================================*/
void CMovable::Animate(int deltaTime)
{
    // Animate object when moving
    if (this->m_VerticalMovingDirection != EDirection::DIRECTION_NONE ||
        this->m_HorizontalMovingDirection != EDirection::DIRECTION_NONE)
    {
        CGameObject::Animate(deltaTime);
    }
}

