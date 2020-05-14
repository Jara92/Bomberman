/**
 * @author Jaroslav Fikar
 * 
*/


#include "CMovable.h"

void CMovable::Draw(CSDLInterface *interface, int cellSize, CCoord offset) const
{
    this->Draw(interface, cellSize, this->m_Location, offset);

    // TODO debug
    interface->SetRenderColor(0,255,0,255);
    SDL_Rect rect {static_cast<int>(this->m_Location.m_X * cellSize),static_cast<int>(this->m_Location.m_Y * cellSize),
                   static_cast<int>(1 * cellSize), static_cast<int>(1 * cellSize)};
    //interface->RenderRectangle(&rect);
    interface->SetRenderColor(255,0,0,255);
}
