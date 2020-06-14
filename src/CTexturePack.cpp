/**
 * @author Jaroslav Fikar
*/

#include "CTexturePack.h"

SDL_Texture *CTexturePack::GetTexture(ETextureType textureType, unsigned int *index) const
{
    auto animation = this->m_Animations.find(textureType);

    // Return animation texture by index if animation exists.
    if (animation != this->m_Animations.end())
    { return animation->second->GetTexture(index); }

    // SDL_Texture * is a C pointer.
    return NULL;
}






