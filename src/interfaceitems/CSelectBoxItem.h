/**
 * @author Jaroslav Fikar
 * 
*/

#pragma once

#include "CText.h"

class CSelectBoxItem : public CInterfaceItem
{
public:
    /**
     * Constructor.
     * @param interface Interface used for texture setup.
     * @param location Item location.
     * @param text Text to be rendered.
     * @param size Item size. Set {0,0} to autosize. Set {0, X} or {X, 0} to autosize one dimension.
     * @param texturePath Path to texture.
     */
    CSelectBoxItem(CSDLInterface *interface, CCoord<> location, const std::string &text, CCoord<> size,
                   SDL_Colour itemColor, SDL_Colour itemHoverColor, SDL_Colour itemActivateColor
    )
            : CInterfaceItem(location, size), m_IsActive(false), m_IsHovering(false)
    {
        this->m_Text = std::make_unique<CText>(interface, location, text, size, itemColor);
        this->m_HoverText = std::make_unique<CText>(interface, location, text, size, itemHoverColor);
        this->m_ActiveText = std::make_unique<CText>(interface, location, text, size, itemActivateColor);

        // Set item size to be equal to text size.
        this->m_Size = this->m_Text->GetSize();
    }

    virtual ~CSelectBoxItem()
    {  }

    /* I dont want allow copying this object. It is unnecessary.
    * This is pointer to some C structure which cant be copied.
    */
    CSelectBoxItem(const CSelectBoxItem &other) = delete;

    CSelectBoxItem &operator=(const CSelectBoxItem &other) = delete;

    virtual void Update(int deltaTime) override
    {}

    virtual void Draw(CSDLInterface *interface) override ;

    virtual void SetLocation(CCoord <>location) override;

    virtual void SetSize(CCoord <>size) override;

    void SetActive(bool active)
    {this->m_IsActive = active;}

    void SetHover(bool hover)
    {this->m_IsHovering = hover;}

protected:
    std::unique_ptr<CText> m_Text;
    std::unique_ptr<CText> m_HoverText;
    std::unique_ptr<CText> m_ActiveText;

    bool m_IsActive;
    bool m_IsHovering;

    virtual void MouseButtonEventHandler(SDL_MouseButtonEvent &e) override;

    virtual void MouseMoveEventHandler(SDL_MouseMotionEvent &e) override;
};

