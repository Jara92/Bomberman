/**
 * @author Jaroslav Fikar
 * 
*/


#include "CText.h"

void CText::SetText(CSDLInterface *interface, const std::string &text, SDL_Color color)
{
    this->m_Text = text;

    // Delete old texture
    if (this->m_Texture != NULL)
    { SDL_DestroyTexture(this->m_Texture); }

    // Get new texture
    CCoord<unsigned int> size;
    this->m_Texture = interface->LoadTextTexture(text, size, color);

    // Set size according to current size
    // Autosize X and Y
    if (this->m_Size.m_X == 0 && this->m_Size.m_Y == 0)
    { this->m_Size = size.ToDouble(); }
        // Autosize X
    else if (this->m_Size.m_X == 0)
    {
        // Keep image aspect ratio.
        double q = this->m_Size.m_Y / size.m_Y;
        this->m_Size.m_X = size.m_X * q;
    }
        // Autosize Y
    else if (this->m_Size.m_Y == 0)
    {
        // Keep image aspect ratio.
        double q = this->m_Size.m_X / size.m_X;
        this->m_Size.m_Y = size.m_Y * q;
    }
}
/*====================================================================================================================*/
void CText::SetColor(CSDLInterface *interface, SDL_Color color)
{
    this->SetText(interface, this->m_Text, color);
}
