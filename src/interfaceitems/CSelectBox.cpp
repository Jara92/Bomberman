/**
 * @author Jaroslav Fikar
 * 
*/


#include "CSelectBox.h"

CSelectBox::CSelectBox(CSDLInterface *interface, CCoord location, CCoord size, unsigned int fontSize,
                       const std::vector<std::string> &options, SDL_Colour itemColor, SDL_Colour itemHoverColor,
                       SDL_Colour itemSelectedColor)
        : CInterfaceItem(location, size), m_ItemColor(itemColor), m_SelectedItemColor(itemSelectedColor)
{
    double margin = 1.1;
    CCoord itemSize;
    unsigned int locationY = this->m_Location.m_Y;

    for (std::vector<std::string>::size_type i = 0; i < options.size(); i++)
    {
        this->m_Items.push_back(std::make_unique<CButton>(interface, options[i], location, itemColor, itemHoverColor, CCoord(0, fontSize)));

        itemSize = this->m_Items.back()->GetSize();
        this->m_Items.back()->SetLocation(
                CCoord((this->m_Size.m_X / 2) - (itemSize.m_X / 2), locationY += static_cast<unsigned int>(itemSize.m_Y * margin)));
    }
}

/*====================================================================================================================*/
void CSelectBox::Update(int deltaTime)
{
    for (auto item = this->m_Items.begin(); item != this->m_Items.end(); item++)
    {
        item->get()->Update(deltaTime);
    }
}

/*====================================================================================================================*/
void CSelectBox::Draw(CSDLInterface *interface)
{
    for (auto item = this->m_Items.begin(); item != this->m_Items.end(); item++)
    {
        item->get()->Draw(interface);
    }
}

/*====================================================================================================================*/
void CSelectBox::MouseEventHandler(SDL_Event &e)
{
    CInterfaceItem::MouseEventHandler(e);

    for (auto item = this->m_Items.begin(); item != this->m_Items.end(); item++)
    {
        item->get()->MouseEventHandler(e);
    }
}
