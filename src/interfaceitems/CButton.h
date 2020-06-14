/**
 * @author Jaroslav Fikar
 * 
*/

#pragma once

#include <functional>
#include "CInterfaceItem.h"
#include "CText.h"

/**
 * Item which draws some text. The text may be changed on hover event.
 * Callback function called on button click event.
 */
class CButton : public CInterfaceItem
{
public:
    /**
    * Constructor.
     * @param interface Interface to be used.
     * @param text Text to be rendered.
     * @param location Button location.
     * @param textColor Default text color.
     * @param textHoverColor Text color when the button is hovered by the mouse cursor.
     * @param fontSize Font size.
     * @param clickCallBack Function to be call on button click event.
     *
    */
    CButton(CSDLInterface &interface, const std::string &text, CCoord<> location, SDL_Colour textColor,
            SDL_Colour textHoverColor, int fontSize, std::function<void(void)> clickCallBack = []()
    {});

    virtual ~CButton() = default;

    /* I dont want allow copying this object.
    * Object contains pointers on C-structures and It is not easy to copy them.
    */
    CButton(const CButton &other) = delete;

    CButton &operator=(const CButton &other) = delete;

    virtual void Update(CSDLInterface &interface, int deltaTime)
    {
        this->m_Text->Update(interface, deltaTime);
        this->m_TextHover->Update(interface, deltaTime);
    }

    virtual void Draw(CSDLInterface &interface) override;

    virtual void SetLocation(CCoord<> location) override;

    virtual void SetFontSize(CSDLInterface &interface, int fontSize)
    {
        this->m_Text->SetFontSize(fontSize);
        this->m_TextHover->SetFontSize(fontSize);
        this->m_Size = this->m_Text->GetSize();
    }

    /**
     * Process mouse events.
     * @param e Mouse event to be processed.
     */
    virtual void MouseEventHandler(SDL_Event &e) override;

    /**
     * Set new text color.
     * @param interface Interface to create new text.
     * @param color Color to be set.
     */
    void SetColor(CSDLInterface &interface, SDL_Colour color)
    { this->m_Text->SetColor(color); }

    /**
     * Set new hover color
     * @param interface Interface to create new text.
     * @param color Color to be set.
     */
    void SetHoverColor(CSDLInterface &interface, SDL_Colour color)
    { this->m_TextHover->SetColor(color); }

protected:
    /** Text to be rendered. */
    std::unique_ptr<CText> m_Text;
    std::unique_ptr<CText> m_TextHover;
    /** Is player hovering this object? */
    bool m_IsHovering;
    /** Function to be called on click event.*/
    std::function<void(void)> m_ClickCallBack;

    virtual void MouseButtonEventHandler(SDL_MouseButtonEvent &e) override;

    virtual void MouseMoveEventHandler(SDL_MouseMotionEvent &e) override;
};

