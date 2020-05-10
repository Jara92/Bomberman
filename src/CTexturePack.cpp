/**
 * @author Jaroslav Fikar
 * 
*/


#include "CTexturePack.h"

CTexturePack::CTexturePack(CSDLInterface *interface, std::map<ETextureType, const std::string> textures)
{
    auto i = textures.begin();
    while(i != textures.end())
    {
        this->m_Textures.insert(std::pair<ETextureType, SDL_Texture *>(i->first, interface->LoadTexture( i->second)));
        i++;
    }
}

CTexturePack::~CTexturePack()
{
    for (auto i = this->m_Textures.begin(); i != this->m_Textures.end(); i++)
    {
        SDL_DestroyTexture(i->second);
    }
}

SDL_Texture *CTexturePack::GetTexture(ETextureType textureType) const
{
    return this->m_Textures.find(textureType)->second;
}


