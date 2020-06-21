/**
 * @author Jaroslav Fikar
*/

#include "CText.h"

void
CText::SetText(const std::string &text, int fontSize, SDL_Color color = {255, 255, 255, 255})
{
    // Render new text texture only when the color or text changed.
    if (this->m_Text == text && color.a == this->m_Color.a && color.b == this->m_Color.b &&
        color.g == this->m_Color.g && color.r == this->m_Color.r && fontSize == this->m_FontSize)
    { return; }

    // Set new values.
    this->m_Text = text;
    this->m_FontSize = fontSize;
    this->m_Color = color;

    // Object must be refreshed in next Update().
    this->m_IsActual = false;
}
/*====================================================================================================================*/
void CText::ReloadContent(CSDLInterface &interface)
{

    // Delete old texture
    if (this->m_Texture != NULL)
    { SDL_DestroyTexture(this->m_Texture); }

    // Get new texture
    CCoord<unsigned int> defaultSize;
    this->m_Texture = interface.LoadTextTexture(this->m_Text, defaultSize, this->m_Color,
                                                static_cast<int>(this->m_FontSize / 1.5));

    // Calculate text width.
    double q = static_cast<double>(this->m_FontSize) / defaultSize.m_Y;
    this->m_Size = CCoord<>(defaultSize.m_X * q, this->m_FontSize);

    this->m_IsActual = true;
}
