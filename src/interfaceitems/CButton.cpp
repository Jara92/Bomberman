/**
 * @author Jaroslav Fikar
 * 
*/


#include "CButton.h"

void CButton::Draw(CSDLInterface *interface)
{
    if (this->m_IsHovering)
    { this->m_HoveredText->Draw(interface); }
    else this->m_Text->Draw(interface);
}

/*====================================================================================================================*/
void CButton::SetLocation(CCoord location)
{
    CInterfaceItem::SetLocation(location);

    this->m_Text->SetLocation(location);
    this->m_HoveredText->SetLocation(location);
}

/*====================================================================================================================*/
void CButton::SetSize(CCoord size)
{
    CInterfaceItem::SetSize(size);

    this->m_Text->SetSize(size);
    this->m_HoveredText->SetSize(size);
}

/*====================================================================================================================*/
void CButton::MouseEventHandler(SDL_Event &e)
{
    switch (e.type)
    {
        case SDL_MOUSEBUTTONDOWN:
            this->MouseButtonEventHandler(e.button);
            break;
        case SDL_MOUSEMOTION:
            this->MouseMoveEventHandler(e.motion);
            break;
        default:
            break;
    }
}

/*====================================================================================================================*/
void CButton::MouseButtonEventHandler(SDL_MouseButtonEvent &e)
{
    if (this->MouseCollision(CCoord(e.x, e.y)))
    {
        if (this->m_ClickCallBack)
        { this->m_ClickCallBack(); }
    }
}

/*====================================================================================================================*/
void CButton::MouseMoveEventHandler(SDL_MouseMotionEvent &e)
{
    if (this->MouseCollision(CCoord(e.x, e.y)))
    {
        this->m_IsHovering = true;
    } else
    {
        this->m_IsHovering = false;
    }
}

/*====================================================================================================================*/
bool CButton::MouseCollision(CCoord mouseLocation) const
{
    if (mouseLocation.m_X >= this->m_Location.m_X && mouseLocation.m_X <= this->m_Location.m_X + this->m_Size.m_X &&
        mouseLocation.m_Y >= this->m_Location.m_Y && mouseLocation.m_Y <= this->m_Location.m_Y + this->m_Size.m_Y)
    { return true; }
    else
    { return false; }
}
