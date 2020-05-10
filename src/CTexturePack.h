/**
 * @author Jaroslav Fikar
 * 
*/

#pragma once
#include <iostream>
#include <map>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "CSDLInterface.h"

enum ETextureType{
    TEXTURE_STATIC,
    TEXTURE_UP,
    TEXTURE_DOWN,
    TEXTURE_LEFT,
    TEXTURE_RIGHT
};

class CTexturePack
{
public:
    CTexturePack(CSDLInterface * interface, std::map<ETextureType, const std::string> textures);
    CTexturePack(std::map<ETextureType, const char *> other) = delete;
    CTexturePack operator = (CTexturePack & other) = delete;
    ~CTexturePack();

    SDL_Texture * GetTexture(ETextureType textureType) const;
protected:
    std::map<ETextureType, SDL_Texture *> m_Textures;
};

