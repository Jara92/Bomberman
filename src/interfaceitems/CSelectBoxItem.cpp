/**
 * @author Jaroslav Fikar
 * 
*/


#include "CSelectBoxItem.h"

/*====================================================================================================================*/
void CSelectBoxItem::Draw(CSDLInterface &interface)
{
    if (this->m_IsActive)
    { this->m_ActiveText->Draw(interface); }
    else if (this->m_IsHovering)
    { this->m_HoverText->Draw(interface); }
    else
    { this->m_Text->Draw(interface); }
}

/*====================================================================================================================*/
void CSelectBoxItem::SetLocation(CCoord<> location)
{
    CInterfaceItem::SetLocation(location);

    this->m_Text->SetLocation(location);
    this->m_HoverText->SetLocation(location);
    this->m_ActiveText->SetLocation(location);
}

/*====================================================================================================================*/
void CSelectBoxItem::SetSize(CCoord<> size)
{
    CInterfaceItem::SetSize(size);

    this->m_Text->SetSize(size);
    this->m_HoverText->SetSize(size);
    this->m_ActiveText->SetSize(size);
}
