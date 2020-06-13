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
 * UI item.
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
     * Set item location.
     * @param location New location.
     */
    virtual void SetLocation(CCoord<> location)
    { this->m_Location = location; }

    /**
     * Handle mouse events.
     * @param e Event structure.
     */
    virtual void MouseEventHandler(SDL_Event & e)
    {}

    /**
     * Set item size.
     * @param size New size.
     */
   virtual  void SetSize(CCoord<> size)
    { this->m_Size = size; }

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

    /**
    * Is this button colliding with mouse?
    * @param mouseLocation Current mouse location.
    * @return True - Colliding.
    */
    bool MouseCollision(CCoord <unsigned int> mouseLocation) const;

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

