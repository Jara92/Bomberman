/**
 * @author Jaroslav Fikar
 * 
*/


#include "CText.h"

void
CText::SetText(CSDLInterface &interface, const std::string &text, int fontSize, SDL_Color color = {255, 255, 255, 255})
{
    // Render new text texture only when the color or text changed.
    if (this->m_Text == text && color.a == this->m_Color.a && color.b == this->m_Color.b &&
        color.g == this->m_Color.g && color.r == this->m_Color.r && fontSize == this->m_FontSize)
    { return; }

    this->m_Text = text;
    this->m_FontSize = fontSize;
    this->m_Color = color;

    // Delete old texture
    if (this->m_Texture != NULL)
    { SDL_DestroyTexture(this->m_Texture); }

    // Get new texture
    CCoord<unsigned int> defaultSize;
    this->m_Texture = interface.LoadTextTexture(text, defaultSize, color, static_cast<int>(fontSize / 1.5));

    // Calculate text width.
    double q = static_cast<double>(fontSize) / defaultSize.m_Y;
    this->m_Size = CCoord<>(defaultSize.m_X * q, fontSize);
}
