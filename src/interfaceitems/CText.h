/**
 * @author Jaroslav Fikar
 * 
*/

#pragma once

#include "CInterfaceItem.h"

class CText : public CInterfaceItem
{
public:
    /**
     * Constructor.
     * @param interface Interface used for texture setup.
     * @param location Item location.
     * @param text Text to be rendered.
     * @param size Item size. Set {0,0} to autosize. Set {0, X} or {X, 0} to autosize one dimension.
     * @param texturePath Path to texture.
     */
    CText(CSDLInterface *interface, CCoord location, const std::string &text, CCoord size = {0, 0},
          SDL_Color color = {255, 255, 255, 255}
    ) : CInterfaceItem(location, size), m_Texture(NULL)
    {
        this->SetText(interface, text, color);
    }

    ~CText()
    { SDL_DestroyTexture(this->m_Texture); }

    /* I dont want allow copying this object. It is unnecessary.
    * This is pointer to some C structure which cant be copied.
    */
    CText(const CText &other) = delete;

    CText &operator=(const CText &other) = delete;

    /**
     * Change displayed text.
     * @param interface Interface to be used.
     * @param text Text to be set.
     */
    void SetText(CSDLInterface *interface, const std::string &text, SDL_Color color = {255, 255, 255, 255});

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
    virtual void Draw(CSDLInterface *interface)
    { interface->RenderTexture(this->m_Texture, this->m_Location, this->m_Size); }

protected:
    SDL_Texture *m_Texture;
};

