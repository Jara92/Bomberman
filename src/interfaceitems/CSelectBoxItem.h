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
     * @param itemColor Default item color.
     * @param itemHoverColor Color of the item when the mouse is hovering it.
     * @param itemActivateColor Color of the item when the item is selected.
     */
    CSelectBoxItem(CSDLInterface &interface, CCoord<> location, const std::string &text, CCoord<> size,
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

    virtual ~CSelectBoxItem() = default;

    /* I dont want allow copying this object.
    * Object contains pointers on C-structures and It is not easy to copy them.
    */
    CSelectBoxItem(const CSelectBoxItem &other) = delete;

    CSelectBoxItem &operator=(const CSelectBoxItem &other) = delete;

    virtual void Update(int deltaTime) override
    {}

    virtual void Draw(CSDLInterface &interface) override ;

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
};

