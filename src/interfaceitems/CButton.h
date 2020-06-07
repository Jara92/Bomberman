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
     * @param text Text to be rendered.
     * @param hoveredText Text to be rendered when the button is being hovered.
    */
    CButton(CSDLInterface *interface, const std::string &text, CCoord location, SDL_Colour textColor,
            SDL_Colour textHoverColor, CCoord size = {0, 0},
            std::function<void(void)> clickCallBack = []()
            {})
            : CInterfaceItem(location, size),
              m_IsHovering(false),m_ClickCallBack(std::move(clickCallBack))
    {
        // Create textures.
        this->m_Text = std::make_unique<CText>(interface, location, text, size, textColor);
        this->m_TextHover = std::make_unique<CText>(interface, location, text, size, textHoverColor);

        // Set size.
        this->m_Size = this->m_Text->GetSize();
    }

    virtual ~CButton() = default;

    /* I dont want allow copying this object. It is unnecessary.
    * This is pointer to some C structure which cant be copied.
    */
    CButton(const CButton &other) = delete;

    CButton &operator=(const CButton &other) = delete;

    /**
     * Update item.
     * @param deltaTime Delta time.
     */
    virtual void Update(int deltaTime)
    {}

    /**
     * Draw item.
     * @param interface Interface to be used.
     */
    virtual void Draw(CSDLInterface *interface);

    virtual void SetLocation(CCoord location) override;

    virtual void SetSize(CCoord size) override;

    /**
     * Process mouse events.
     * @param e Mouse event to be processed.
     */
    virtual void MouseEventHandler(SDL_Event &e) override;

    void SetColor(CSDLInterface * interface, SDL_Colour color)
    {this->m_Text->SetColor(interface, color);}

    void SetHoverColor(CSDLInterface * interface, SDL_Colour color)
    {this->m_TextHover->SetColor(interface, color);}

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

    /**
     * Is this button colliding with mouse?
     * @param mouseLocation Current mouse location.
     * @return True - Colliding.
     */
    bool MouseCollision(CCoord mouseLocation) const;
};

