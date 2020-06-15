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
    { this->SetText(text, fontSize, color);
        this->ReloadContent(interface);}

    virtual ~CText()
    { SDL_DestroyTexture(this->m_Texture); }

    /* I dont want allow copying this object.
    * Object contains pointers on C-structures and It is not easy to copy them.*/
    CText(const CText &other) = delete;

    CText &operator=(const CText &other) = delete;

    virtual void Draw(CSDLInterface &interface) override
    { interface.RenderTexture(this->m_Texture, this->m_Location, this->m_Size); }

    virtual void ReloadContent(CSDLInterface &interface) override;

    /**
     * Change displayed text.
     * @param text Text to be set.
     * @param fontSize Font size.
     * @param color Color to be set.
     */
    void SetText(const std::string &text, int fontSize, SDL_Color color);

    /**
     * Change text color.
     * @param color Color to be set.
     */
    void SetColor(SDL_Color color)
    { this->SetText(this->m_Text, this->m_FontSize, color); }

    void SetFontSize(int fontSize)
    { this->SetText(this->m_Text, fontSize, this->m_Color); }

    SDL_Colour GetColor() const
    { return this->m_Color; }

protected:
    SDL_Texture *m_Texture;
    std::string m_Text;
    int m_FontSize;
    SDL_Colour m_Color;
};

