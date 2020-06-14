/**
 * @author Jaroslav Fikar
 * 
*/

#pragma once

#include <SDL2/SDL_system.h>
#include <SDL2/SDL_image.h>
#include "../CSDLInterface.h"
#include "../CCoord.h"

/** UI item. */
class CInterfaceItem
{
public:
    /**
     * Constructor.
     * @param location Item location.
     * @param size Item size.
     */
    explicit CInterfaceItem(CCoord <> location, CCoord<> size = {0,0})
            : m_Location(location), m_Size(size)
    {}

    virtual ~CInterfaceItem() = default;

    /* This abstract class does not contain any C pointers - We can easily copy it. */
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
    virtual void Draw(CSDLInterface &interface) = 0;

    /**
     * Handle mouse events.
     * @param e Event structure.
     */
    virtual void MouseEventHandler(SDL_Event & e)
    {}

    /**
    * Is this button colliding with mouse?
    * @param mouseLocation Current mouse location.
    * @return True - Colliding.
    */
    bool MouseCollision(CCoord <unsigned int> mouseLocation) const;

    /**
     * Set item location.
     * @param location New location.
     */
    virtual void SetLocation(CCoord<> location)
    { this->m_Location = location; }

    /**
    * Get object top-left corner location.
    * @return Location.
    */
    CCoord<> GetLocation() const
    {return this->m_Location;}

    /**
     * Get object size.
     * @return Object size.
     */
    CCoord <>GetSize() const
    {return this->m_Size;}

protected:
    CCoord <>m_Location;
    CCoord <>m_Size;

    /**
     * Handle mouse click
     * @param e Event structure.
     */
    virtual void MouseButtonEventHandler(SDL_MouseButtonEvent & e)
    {}

    /**
    * Handle mouse move.
    * @param e Event structure.
    */
    virtual void MouseMoveEventHandler(SDL_MouseMotionEvent & e)
    {}
};

