/**
 * @author Jaroslav Fikar
 * 
*/


#include "CAnimation.h"

CAnimation::CAnimation(CSDLInterface *interface, const std::map<unsigned int, const std::string > &textures)
{
    auto i = textures.begin();
    while (i != textures.end())
    {
        this->m_Textures.insert(std::pair<unsigned int, SDL_Texture *>(i->first, interface->LoadTexture(i->second)));
        i++;
    }
}
/*====================================================================================================================*/
CAnimation::~CAnimation()
{
    for (auto i = this->m_Textures.begin(); i != this->m_Textures.end(); i++)
    {
        SDL_DestroyTexture(i->second);
    }
}
/*====================================================================================================================*/
SDL_Texture *CAnimation::GetTexture(unsigned int * index) const
{
    // Handle animation index overflow
    if(*index >= this->m_Textures.size())
    {*index = 0; }

    // Return correct texture
    return this->m_Textures.find(*index)->second;
}
