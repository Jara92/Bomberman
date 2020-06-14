/**
 * @author Jaroslav Fikar
 * 
*/

#pragma once

#include <map>
#include "CInterfaceItem.h"
#include "CButton.h"
#include "CText.h"
#include "CSelectBoxItem.h"

template<class T>
class CSelectBox : public CInterfaceItem
{
public:
    CSelectBox(CSDLInterface &interface, CCoord<> location, CCoord<> size, unsigned int fontSize,
               const std::map<std::string, T> &options, CCoord<unsigned int> defaultOption, SDL_Colour itemColor,
               SDL_Colour itemHoverColor, SDL_Colour itemSelectedColor, std::function<void(T)> callback = {});

    virtual ~CSelectBox() = default;

    /* I dont want allow copying this object.
    * Object contains pointers on C-structures and It is not easy to copy them.
    */
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
    virtual void Draw(CSDLInterface &interface) override
    {
        for (auto item = this->m_Items.begin(); item != this->m_Items.end(); item++)
        { item->second->Draw(interface); }
    }

    virtual void MouseEventHandler(SDL_Event &e) override;

protected:
    std::map<T, std::unique_ptr<CSelectBoxItem>> m_Items;
    std::function<void(T)> m_CallBack;
    T m_SelectedValue;
    SDL_Colour m_ItemColor;
    SDL_Colour m_SelectedItemColor;

    void DeactivateAll();

    virtual void MouseButtonEventHandler(SDL_MouseButtonEvent &e) override;

    virtual void MouseMoveEventHandler(SDL_MouseMotionEvent &e) override;
};

template<class T>
CSelectBox<T>::CSelectBox(CSDLInterface &interface, CCoord<> location, CCoord<> size, unsigned int fontSize,
                          const std::map<std::string, T> &options, CCoord<unsigned int> defaultOption,
                          SDL_Colour itemColor, SDL_Colour itemHoverColor, SDL_Colour itemSelectedColor,
                          std::function<void(T)> callback)
        : CInterfaceItem(location, size), m_CallBack(std::move(callback)), m_ItemColor(itemColor),
          m_SelectedItemColor(itemSelectedColor)
{
    double margin = 1.1;
    CCoord<> itemSize;
    unsigned int locationY = this->m_Location.m_Y;

    // Is some item marked as selected?
    bool defaultWasSet = false;

    // Create button for every option.
    for (auto option = options.begin(); option != options.end(); option++)
    {
        std::unique_ptr<CSelectBoxItem> item = std::make_unique<CSelectBoxItem>(interface, CCoord<>(0, 0),
                                                                                option->first, fontSize, itemColor,
                                                                                itemHoverColor, itemSelectedColor);
        itemSize = item->GetSize();
        item->SetLocation(CCoord<>((this->m_Size.m_X / 2) - (itemSize.m_X / 2),
                                   locationY += static_cast<unsigned int>(itemSize.m_Y * margin)));

        if (option->second == defaultOption)
        {
            item->SetActive(true);
            defaultWasSet = true;
        }

        this->m_Items.insert({option->second, std::move(item)});
    }

    // Set first as selected if there is no selected item.
    if (!defaultWasSet && this->m_Items.begin() != this->m_Items.end())
    { this->m_Items.begin()->second->SetActive(true); }
}

/*====================================================================================================================*/
template<class T>
void CSelectBox<T>::Update(int deltaTime)
{
    for (auto item = this->m_Items.begin(); item != this->m_Items.end(); item++)
    { item->second->Update(deltaTime); }
}

/*====================================================================================================================*/
template<class T>
void CSelectBox<T>::MouseEventHandler(SDL_Event &e)
{
    CInterfaceItem::MouseEventHandler(e);

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
template<class T>
void CSelectBox<T>::MouseButtonEventHandler(SDL_MouseButtonEvent &e)
{
    CInterfaceItem::MouseButtonEventHandler(e);

    for (auto item = this->m_Items.begin(); item != this->m_Items.end(); item++)
    {
        if (item->second->MouseCollision(CCoord<unsigned int>(e.x, e.y)))
        {
            this->DeactivateAll();
            item->second->SetActive(true);

            T output = item->first;
            if (this->m_CallBack)
            { this->m_CallBack(output); }
        }
    }
}

/*====================================================================================================================*/
template<class T>
void CSelectBox<T>::MouseMoveEventHandler(SDL_MouseMotionEvent &e)
{
    CInterfaceItem::MouseMoveEventHandler(e);

    for (auto item = this->m_Items.begin(); item != this->m_Items.end(); item++)
    {
        if (item->second->MouseCollision(CCoord<unsigned int>(e.x, e.y)))
        { item->second->SetHover(true); }
        else
        { item->second->SetHover(false); }
    }
}

/*====================================================================================================================*/
template<class T>
void CSelectBox<T>::DeactivateAll()
{
    for (auto item = this->m_Items.begin(); item != this->m_Items.end(); item++)
    { item->second->SetActive(false); }
}

