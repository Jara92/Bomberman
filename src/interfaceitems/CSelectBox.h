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
    CSelectBox(CSDLInterface *interface, CCoord location, CCoord size, unsigned int fontSize, const std::vector<std::string> & options,
               SDL_Colour itemColor, SDL_Colour itemHoverColor, SDL_Colour itemSelectedColor);

    virtual ~CSelectBox() = default;

    CSelectBox(const CSelectBox &other) = delete;

    CSelectBox &operator=(const CSelectBox &other) = delete;

    /**
     * Update item.
     * @param deltaTime Delta time.
     */
    virtual void Update(int deltaTime) override ;

    /**
     * Draw item.
     * @param interface Interface to be used.
     */
    virtual void Draw(CSDLInterface *interface) override ;

    virtual void MouseEventHandler(SDL_Event & e) override ;

protected:
    std::vector<std::unique_ptr<CButton>> m_Items;


};

