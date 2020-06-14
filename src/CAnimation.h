/**
 * @author Jaroslav Fikar
 * 
*/

#pragma once

#include <iostream>
#include <vector>
#include <memory>
#include <SDL2/SDL.h>
#include <SDL2/SDL_system.h>
#include <SDL2/SDL_image.h>
#include "enums/ETextureType.h"
#include "CSDLInterface.h"

/** Animated texture simulation. */
class CAnimation
{
public:
    /**
     * Animation constructor.
     * @param interface Interface to be used.
     * @param textures Animation textures.
     */
    CAnimation(CSDLInterface &interface, const std::vector<std::string> &textures)
    {
        for (std::vector<std::string>::size_type i = 0; i < textures.size(); i++)
        { this->m_Textures.push_back(interface.LoadTexture(textures[i])); }
    }

    ~CAnimation()
    {
        // We need destroy every single textures.
        for (std::vector<std::string>::size_type i = 0; i < this->m_Textures.size(); i++)
        { SDL_DestroyTexture(this->m_Textures[i]); }
        this->m_Textures.clear();
    }

    /* I dont want allow copying this object. It is unnecessary.
     * This object is saved in CTexture pack and gameobjects have shared_ptr to their texturepack object.*/
    CAnimation(const CAnimation &other) = delete;

    CAnimation &operator=(const CAnimation &other) = delete;

    SDL_Texture *GetTexture(unsigned int *index) const;

protected:
    std::vector<SDL_Texture *> m_Textures;
};
