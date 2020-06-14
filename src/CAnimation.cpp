/**
 * @author Jaroslav Fikar
*/

#include "CAnimation.h"

SDL_Texture *CAnimation::GetTexture(unsigned int *index) const
{
    // Handle animation index overflow
    if (*index >= this->m_Textures.size())
    { *index = 0; }

    // Get correct texture
    SDL_Texture *texture = this->m_Textures[*index];
    if (texture)
    { return texture; }

    // SDL_Texture * is C pointer
    return NULL;
}
