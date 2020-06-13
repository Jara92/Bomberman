/**
 * @author Jaroslav Fikar
 * 
*/

#pragma once
#include "CInterfaceItem.h"

class CImage : public CInterfaceItem
{
public:
    /**
     * Constructor.
     * @param interface Interface used for texture setup.
     * @param location Item location. Use {0,0} to center location. Use {0, X} or {X, 0} to center one direction.
     * @param size Item size.
     * @param texturePath Path to texture.
     */
    CImage(CSDLInterface & interface, CCoord <>location, CCoord<> size, std::string texturePath)
    : CInterfaceItem(location, size)
    {
        this->m_Texture = interface.LoadTexture( texturePath);
    }

    virtual ~CImage()
    {SDL_DestroyTexture(this->m_Texture);}

    /* I dont want allow copying this object.
    * Object contains pointers on C-structures and It is not easy to copy them.
    */
    CImage(const CImage &other) = delete;
    CImage &operator=(const CImage &other) = delete;

    /**
     * Update item.
     * @param deltaTime Delta time.
     */
    virtual void Update(int deltaTime)
    {}

    /**
     * Draw item.
     * @param interface Interface to be used.
     */
    virtual void Draw(CSDLInterface &interface)
    {interface.RenderTexture(this->m_Texture, this->m_Location, this->m_Size);}

protected:
    SDL_Texture * m_Texture;
};

