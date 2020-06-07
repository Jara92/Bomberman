/**
 * @author Jaroslav Fikar
 * 
*/


#include "CSelectBox.h"

CSelectBox::CSelectBox(CSDLInterface *interface, CCoord location, unsigned int fontSize,
                       const std::vector<std::string> & options, SDL_Colour itemColor, SDL_Colour itemHoverColor,
                       SDL_Colour itemSelectedColor)
        : CInterfaceItem(location, CCoord(0, 0))
{
  /*  double margin = 1.1;
    CCoord windowSize = interface->GetWindowSize();
    CCoord itemSize;

    for (std::vector<std::string>::size_type  i = 0; i < options.size(); i++)
    {
        std::unique_ptr<CText> text = std::make_unique<CText>(interface, CCoord(0,0), options[i], CCoord(0, fontSize), itemColor);
        std::unique_ptr<CText> hoverText = std::make_unique<CText>(interface, CCoord(0,0), options[i], CCoord(0, fontSize), itemHoverColor);
        std::unique_ptr<CText> selectedText = std::make_unique<CText>(interface, CCoord(0,0), options[i], CCoord(0, fontSize), itemSelectedColor);
    }*/
}
