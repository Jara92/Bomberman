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
     * @param fontSize Font size.
     * @param texturePath Path to texture.
     */
    CText(CSDLInterface &interface, CCoord<> location, const std::string &text, int fontSize,
          SDL_Color color = {255, 255, 255, 255}
    ) : CInterfaceItem(location), m_Texture(NULL), m_Text(""), m_FontSize(0), m_Color()
    {
        this->SetText(interface, text, fontSize, color);
    }

    virtual ~CText()
    { SDL_DestroyTexture(this->m_Texture); }

    /* I dont want allow copying this object.
    * Object contains pointers on C-structures and It is not easy to copy them.*/
    CText(const CText &other) = delete;

    CText &operator=(const CText &other) = delete;

    /**
     * Change displayed text.
     * @param interface Interface to be used.
     * @param text Text to be set.
     * @param fontSize Font size.
     * @param color Color to be set.
     */
    void SetText(CSDLInterface &interface, const std::string &text, int fontSize, SDL_Color color);

    /**
     * Change text color.
     * @param interface Interface to be used.
     * @param color Color to be set.
     */
    void SetColor(CSDLInterface &interface, SDL_Color color)
    { this->SetText(interface, this->m_Text, this->m_FontSize, color); }

    void SetFontSize(CSDLInterface &interface, int fontSize)
    { this->SetText(interface, this->m_Text, fontSize, this->m_Color); }

    /**
     * Update item.
     * @param deltaTime Delta time.
     */
    virtual void Update(int deltaTime) override
    {}

    /**
     * Draw item.
     * @param interface Interface to be used.
     */
    virtual void Draw(CSDLInterface &interface) override
    { interface.RenderTexture(this->m_Texture, this->m_Location, this->m_Size); }

    SDL_Colour GetColor() const
    { return this->m_Color; }

protected:
    SDL_Texture *m_Texture;
    std::string m_Text;
    int m_FontSize;
    SDL_Colour m_Color;
};

