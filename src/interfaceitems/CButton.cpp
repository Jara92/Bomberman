/**
 * @author Jaroslav Fikar
*/

#include "CButton.h"

CButton::CButton(CSDLInterface &interface, const std::string &text, CCoord<> location, SDL_Colour textColor,
                 SDL_Colour textHoverColor, int fontSize, std::function<void(void)> clickCallBack)
        : CInterfaceItem(location),
          m_IsHovering(false), m_ClickCallBack(std::move(clickCallBack))
{
    // Create textures.
    this->m_Text = std::make_unique<CText>(interface, location, text, fontSize, textColor);
    this->m_TextHover = std::make_unique<CText>(interface, location, text, fontSize, textHoverColor);

    // Set size.
    this->m_Size = this->m_Text->GetSize();
}

/*====================================================================================================================*/
void CButton::Draw(CSDLInterface &interface)
{
    if (this->m_IsHovering)
    { this->m_TextHover->Draw(interface); }
    else
    { this->m_Text->Draw(interface); }
}

/*====================================================================================================================*/
void CButton::SetLocation(CCoord<> location)
{
    CInterfaceItem::SetLocation(location);

    this->m_Text->SetLocation(location);
    this->m_TextHover->SetLocation(location);
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
    { this->m_IsHovering = true; }
    else
    { this->m_IsHovering = false; }
}


