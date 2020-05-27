/**
 * @author Jaroslav Fikar
 * 
*/


#include "CAnimation.h"

CAnimation::CAnimation(CSDLInterface *interface, const std::vector< std::string > &textures)
{
    for(std::vector<std::string>::size_type i = 0; i < textures.size(); i++)
    {
        this->m_Textures.push_back(interface->LoadTexture(textures[i]));
    }
}
/*====================================================================================================================*/
CAnimation::~CAnimation()
{
    for(std::vector<std::string>::size_type i = 0; i < this->m_Textures.size(); i++)
    {
        SDL_DestroyTexture( this->m_Textures[i]);
    }
    this->m_Textures.clear();
}
/*====================================================================================================================*/
SDL_Texture *CAnimation::GetTexture(unsigned int * index) const
{
    // Handle animation index overflow
    if(*index >= this->m_Textures.size())
    {*index = 0; }

    // Get correct texture
    SDL_Texture * texture = this->m_Textures[*index];
    if(texture)
    {
        return texture;
    }

    // SDL_Texture * is C pointer
    return NULL;
}
