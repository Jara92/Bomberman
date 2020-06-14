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
    : CInterfaceItem(location, size), m_Texture(NULL), m_TexturePath(texturePath)
    { this->Refresh(interface);   }

    virtual ~CImage()
    {SDL_DestroyTexture(this->m_Texture);}

    /* I dont want allow copying this object.
    * Object contains pointers on C-structures and It is not easy to copy them.
    */
    CImage(const CImage &other) = delete;
    CImage &operator=(const CImage &other) = delete;

    virtual void Draw(CSDLInterface &interface)
    {interface.RenderTexture(this->m_Texture, this->m_Location, this->m_Size);}

    virtual void Refresh(CSDLInterface & interface) override
    {
        if(this->m_Texture)
        {SDL_DestroyTexture(this->m_Texture);}
        this->m_Texture = interface.LoadTexture( this->m_TexturePath);
        this->m_IsActual = true;
    }

    /**
    * Set item size.
     * @param size New size.
    */
    virtual  void SetSize(CCoord<> size)
    { this->m_Size = size; }

protected:
    SDL_Texture * m_Texture;
    std::string m_TexturePath;
};

