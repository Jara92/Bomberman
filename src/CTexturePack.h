/**
 * @author Jaroslav Fikar
 * 
*/

#pragma once

#include <iostream>
#include <map>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "ETextureType.h"
#include "CAnimation.h"
#include "CSDLInterface.h"

class CTexturePack
{
public:
    /**
     *
     * @param interface Interface
     * @param textures Textures to be rendered.
     * @param isCentered Is this texture centered?
     * @param textureSize Texture size
     */
    CTexturePack(CSDLInterface *interface, std::map<ETextureType, const std::vector<std::string> > &textures,
                 bool isCentered = true, CCoord<> textureSize = CCoord<>(1, 1));

    /* I dont want to allow copying this objekt. It does not make sense to copy object which could not be changed.
     * It is better to use pointer to 1 common objekt to save memory. */
    CTexturePack(const CTexturePack &other) = delete;

    CTexturePack operator=(CTexturePack &other) = delete;

    ~CTexturePack();

    /**
     * Return texture by texturetype
     * @param textureType Texturetype to be returned
     * @return Texture or nullptr if not found.
     */
    SDL_Texture *GetTexture(ETextureType textureType, unsigned int *index) const;

    CCoord<> GetTextureSize() const
    { return this->m_TextureSize; }

    /**
     * Is this texture centered in target cell?
     * @return True - Is centered.
     */
    bool IsCentered() const
    { return this->m_IsCentered; }

protected:
    std::map<ETextureType, CAnimation *> m_Animations;
    CCoord<> m_TextureSize;
    /** Is this texture centered in target cell? */
    bool m_IsCentered;
};

