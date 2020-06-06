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
    {
        if(false && this->m_ClickCallBack)// todo click
        {
            this->m_ClickCallBack();
        }
    }

    /**
     * Draw item.
     * @param interface Interface to be used.
     */
    virtual void Draw(CSDLInterface *interface)
    {
        if (this->m_IsHovering)
        { this->m_HoveredText->Draw(interface); }
        else this->m_Text->Draw(interface);
    }

    virtual void SetLocation(CCoord location) override
    {
        CInterfaceItem::SetLocation(location);

        this->m_Text->SetLocation(location);
        this->m_HoveredText->SetLocation(location);
    }

    virtual void SetSize(CCoord size) override
    {
        CInterfaceItem::SetSize(size);

        this->m_Text->SetSize(size);
        this->m_HoveredText->SetSize(size);
    }

protected:
    std::unique_ptr<CText> m_Text;
    std::unique_ptr<CText> m_HoveredText;
    std::function<void(void)> m_ClickCallBack;

    bool m_IsHovering;
};

