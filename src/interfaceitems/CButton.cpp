/**
 * @author Jaroslav Fikar
 * 
*/


#include "CButton.h"

void CButton::Draw(CSDLInterface *interface)
{
    if(this->m_IsHovering)
    {this->m_TextHover->Draw(interface);}
    else
    {this->m_Text->Draw(interface);}
}

/*====================================================================================================================*/
void CButton::SetLocation(CCoord <>location)
{
    CInterfaceItem::SetLocation(location);

    this->m_Text->SetLocation(location);
    this->m_TextHover->SetLocation(location);
}

/*====================================================================================================================*/
void CButton::SetSize(CCoord <>size)
{
    CInterfaceItem::SetSize(size);

    this->m_Text->SetSize(size);
    this->m_TextHover->SetSize(size);
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
    if (this->MouseCollision(CCoord<unsigned int>(e.x, e.y)))
    {
        if (this->m_ClickCallBack)
        { this->m_ClickCallBack(); }
    }
}

/*====================================================================================================================*/
void CButton::MouseMoveEventHandler(SDL_MouseMotionEvent &e)
{
    if (this->MouseCollision(CCoord<unsigned int>(e.x, e.y)))
    {
        this->m_IsHovering = true;
    } else
    {
        this->m_IsHovering = false;
    }
}
