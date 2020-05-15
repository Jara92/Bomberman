/**
 * @author Jaroslav Fikar
 * 
*/

#pragma once

#include <iostream>
#include <map>
#include <memory>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "ETextureType.h"
#include "CSDLInterface.h"

class CAnimation
{
public:
    CAnimation(CSDLInterface *interface, const std::map<unsigned int, const std::string > &textures);

    ~CAnimation();

    /* I dont want allow copying this object. It is unnecessary.
     * This object is saved in CTexture pack and gameobjects have shared_ptr to their texturepack object.
    */
    CAnimation(const CAnimation &other) = delete;
    CAnimation &operator=(const CAnimation &other) = delete;

    SDL_Texture * GetTexture (unsigned int * index) const;

protected:
    std::map<unsigned int, SDL_Texture *> m_Textures;
};

