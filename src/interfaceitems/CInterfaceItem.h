/**
 * @author Jaroslav Fikar
 * 
*/

#pragma once

#include <SDL2/SDL_system.h>
#include <SDL2/SDL_image.h>
#include "../CSDLInterface.h"
#include "../CCoord.h"

/**
 * Item to be interacted by the player.
 */
class CInterfaceItem
{
public:
    /**
     * Constructor.
     * @param location Item location. Use {0,0} to center location. Use {0, X} or {X, 0} to center one direction.
     * @param size Item size.
     */
    explicit CInterfaceItem(CCoord <> location, CCoord <>size)
            : m_Location(location), m_Size(size)
    {}

    virtual ~CInterfaceItem() = default;

    CInterfaceItem(const CInterfaceItem &other) = default;

    CInterfaceItem &operator=(const CInterfaceItem &other) = default;

    /**
     * Update item.
     * @param deltaTime Delta time.
     */
    virtual void Update(int deltaTime) = 0;

    /**
     * Draw item.
     * @param interface Interface to be used.
     */
    virtual void Draw(CSDLInterface *interface) = 0;

    /**
     * Set item location.
     * @param location New location.
     */
    virtual void SetLocation(CCoord<> location)
    { this->m_Location = location; }

    virtual void MouseEventHandler(SDL_Event & e)
    {}

    /**
     * Set item size.
     * @param size New size.
     */
   virtual  void SetSize(CCoord<> size)
    { this->m_Size = size; }

    CCoord<> GetLocation() const
    {return this->m_Location;}

    CCoord <>GetSize() const
    {return this->m_Size;}

protected:
    CCoord <>m_Location;
    CCoord <>m_Size;

    virtual void MouseButtonEventHandler(SDL_MouseButtonEvent & e)
    {}

    virtual void MouseMoveEventHandler(SDL_MouseMotionEvent & e)
    {}
};

