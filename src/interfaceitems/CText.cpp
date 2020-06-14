/**
 * @author Jaroslav Fikar
 * 
*/


#include "CText.h"

void CText::SetText(CSDLInterface &interface, const std::string &text, CCoord<> size, SDL_Color color)
{
    // Render new text texture only when the color or text changed.
    if (this->m_Text == text && color.a == this->m_Color.a && color.b == this->m_Color.b &&
        color.g == this->m_Color.g && color.r == this->m_Color.r)
    { return; }

    this->m_Text = text;

    // Delete old texture
    if (this->m_Texture != NULL)
    { SDL_DestroyTexture(this->m_Texture); }

    // Get new texture
    CCoord<unsigned int> defaultSize;
    this->m_Texture = interface.LoadTextTexture(text, defaultSize, color, static_cast<int>(size.m_Y / 1.5));

    this->m_Size = size;

    // Set size according to current size
    // Autosize X and Y
    if (size.m_X == 0 && size.m_Y == 0)
    { this->m_Size = defaultSize.ToDouble(); }
        // AutodefaultSize X
    else if (size.m_X == 0)
    {
        // Keep image aspect ratio.
        double q = size.m_Y / defaultSize.m_Y;
        this->m_Size.m_X = defaultSize.m_X * q;
    }
        // AutodefaultSize Y
    else if (size.m_Y == 0)
    {
        // Keep image aspect ratio.
        double q = size.m_X / defaultSize.m_X;
        this->m_Size.m_Y = defaultSize.m_Y * q;
    }
}
