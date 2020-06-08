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
    CText(CSDLInterface *interface, CCoord <>location, const std::string &text, CCoord <>size = {0, 0},
          SDL_Color color = {255, 255, 255, 255}
    ) : CInterfaceItem(location, size), m_Texture(NULL), m_Text(text)
    {
        this->SetText(interface, text, color);
    }

    virtual ~CText()
    { SDL_DestroyTexture(this->m_Texture); }

    /* I dont want allow copying this object.
    * Object contains pointers on C-structures and It is not easy to copy them.
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
     * Change text color.
     * @param interface Interface to be used.
     * @param color Color to be set.
     */
    void SetColor(CSDLInterface * interface, SDL_Color color);

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
    std::string m_Text;
};

