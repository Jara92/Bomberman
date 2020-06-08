/**
 * @author Jaroslav Fikar
 * 
*/

#pragma once

#include <map>
#include "CInterfaceItem.h"
#include "CButton.h"

template<class T>
class CSelectBox : public CInterfaceItem
{
public:
    CSelectBox(CSDLInterface *interface, CCoord location, CCoord size, unsigned int fontSize,
               const std::map<std::string, T> &options, SDL_Colour itemColor, SDL_Colour itemHoverColor,
               SDL_Colour itemSelectedColor, std::function<void(T)> callback = {});

    virtual ~CSelectBox() = default;

    CSelectBox(const CSelectBox &other) = delete;

    CSelectBox &operator=(const CSelectBox &other) = delete;

    /**
     * Update item.
     * @param deltaTime Delta time.
     */
    virtual void Update(int deltaTime) override;

    /**
     * Draw item.
     * @param interface Interface to be used.
     */
    virtual void Draw(CSDLInterface *interface) override;

    virtual void MouseEventHandler(SDL_Event &e) override;

    T GetSelectedItemValue() const
    { return this->m_SelectedValue; }

    void UpdateValue(T value)
    {
        this->m_SelectedValue = value;
        if (this->m_CallBack)
        { this->m_CallBack(value); }
        std::cout << "Value: " << this->m_SelectedValue << std::endl;
    }

protected:
    std::vector<std::unique_ptr<CButton>> m_Items;
    std::function<void(T)> m_CallBack;
    T m_SelectedValue;
    SDL_Colour m_ItemColor;
    SDL_Colour m_SelectedItemColor;
};

template<class T>
CSelectBox<T>::CSelectBox(CSDLInterface *interface, CCoord location, CCoord size, unsigned int fontSize,
                          const std::map<std::string, T> &options, SDL_Colour itemColor, SDL_Colour itemHoverColor,
                          SDL_Colour itemSelectedColor, std::function<void(T)> callback)
        : CInterfaceItem(location, size), m_CallBack(std::move(callback)), m_ItemColor(itemColor),
          m_SelectedItemColor(itemSelectedColor)
{
    double margin = 1.1;
    CCoord itemSize;
    unsigned int locationY = this->m_Location.m_Y;

    // Create button for every option.
    for (auto option = options.begin(); option != options.end(); option++)
    {
        std::unique_ptr<CButton> button = std::make_unique<CButton>(interface, option->first, location, itemColor,
                                                                    itemHoverColor,
                                                                    CCoord(0, fontSize), [=]()
                                                                    { this->UpdateValue(option->second); });

        itemSize = button->GetSize();
        button->SetLocation(
                CCoord((this->m_Size.m_X / 2) - (itemSize.m_X / 2),
                       locationY += static_cast<unsigned int>(itemSize.m_Y * margin)));

        this->m_Items.push_back(std::move(button));
    }
}

/*====================================================================================================================*/
template<class T>
void CSelectBox<T>::Update(int deltaTime)
{
    for (auto item = this->m_Items.begin(); item != this->m_Items.end(); item++)
    {
        item->get()->Update(deltaTime);
    }
}

/*====================================================================================================================*/
template<class T>
void CSelectBox<T>::Draw(CSDLInterface *interface)
{
    for (auto item = this->m_Items.begin(); item != this->m_Items.end(); item++)
    {
        item->get()->Draw(interface);
    }
}

/*====================================================================================================================*/
template<class T>
void CSelectBox<T>::MouseEventHandler(SDL_Event &e)
{
    CInterfaceItem::MouseEventHandler(e);

    for (auto item = this->m_Items.begin(); item != this->m_Items.end(); item++)
    {
        item->get()->MouseEventHandler(e);
    }
}

