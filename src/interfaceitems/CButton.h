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
    CButton(std::unique_ptr<CText> text, std::function<void(void)> clickCallBack = []()
    {}, std::unique_ptr<CText> hoveredText = {})
            : CInterfaceItem(text->GetLocation(), text->GetSize()), m_Text(std::move(text)),
              m_HoveredText(std::move(hoveredText)), m_IsHovering(false), m_ClickCallBack(std::move(clickCallBack))
    {}

    ~CButton() = default;

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

protected:
    /** Text to be rendered. */
    std::unique_ptr<CText> m_Text;
    /** Text to be rendered in hover mode. */
    std::unique_ptr<CText> m_HoveredText;
    /** Function to be called on click event.*/
    std::function<void(void)> m_ClickCallBack;

    /** Is player hovering this object? */
    bool m_IsHovering;

    virtual void MouseButtonEventHandler(SDL_MouseButtonEvent &e) override;

    virtual void MouseMoveEventHandler(SDL_MouseMotionEvent &e) override;

    /**
     * Is this button colliding with mouse?
     * @param mouseLocation Current mouse location.
     * @return True - Colliding.
     */
    bool MouseCollision(CCoord mouseLocation) const ;
};

