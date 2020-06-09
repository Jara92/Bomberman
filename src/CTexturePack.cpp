/**
 * @author Jaroslav Fikar
*/

#include "CTexturePack.h"

CTexturePack::CTexturePack(CSDLInterface *interface, std::map<ETextureType, const std::vector<std::string> > &textures,
                           bool isCentered, CCoord<> textureSize) : m_TextureSize(textureSize), m_IsCentered(isCentered)
{
    // For every texture type create CAnimation object
    auto i = textures.begin();
    while (i != textures.end())
    {
        this->m_Animations.insert(
                std::pair<ETextureType, CAnimation *>(i->first, new CAnimation(interface, i->second)));
        i++;
    }
}

/*====================================================================================================================*/
CTexturePack::~CTexturePack()
{
    for (auto i = this->m_Animations.begin(); i != this->m_Animations.end(); i++)
    { delete (i->second); }
}

/*====================================================================================================================*/
SDL_Texture *CTexturePack::GetTexture(ETextureType textureType, unsigned int *index) const
{
    auto animation = this->m_Animations.find(textureType);

    // Return animation texture by index if animation exists
    if (animation != this->m_Animations.end())
    { return animation->second->GetTexture(index); }

    // SDL_Texture * is C pointer
    return NULL;
}






