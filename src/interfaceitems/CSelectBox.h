/**
 * @author Jaroslav Fikar
 * 
*/

#pragma once

#include "CInterfaceItem.h"
#include "CButton.h"

class CSelectBox : public CInterfaceItem
{
public:
    CSelectBox(CSDLInterface *interface, CCoord location, unsigned int fontSize, const std::vector<std::string> & options,
               SDL_Colour itemColor, SDL_Colour itemHoverColor, SDL_Colour itemSelectedColor);

protected:
    std::vector<std::unique_ptr<CButton>> m_Items;
};

