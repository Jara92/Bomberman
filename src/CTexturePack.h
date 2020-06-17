/**
 * @author Jaroslav Fikar
 * 
*/

#pragma once

#include <iostream>
#include <map>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "enums/ETextureType.h"
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
    CTexturePack(CSDLInterface &interface, std::map<ETextureType, const std::vector<std::string> > &textures,
                 bool isCentered = true, CCoord<> textureSize = CCoord<>(1, 1))
            : m_TextureSize(textureSize), m_IsCentered(isCentered)
    {
        // For every texture type create CAnimation object
        for (auto texture = textures.begin(); texture != textures.end(); texture++)
        { this->m_Animations.insert({texture->first, std::make_unique<CAnimation>(interface, texture->second)}); }
    }

    /* I dont want to allow copying this object. It does not make sense to copy object which could not be changed.
     * It is better to use pointer to 1 common object to save memory. */
    CTexturePack(const CTexturePack &other) = delete;

    CTexturePack operator=(CTexturePack &other) = delete;

    ~CTexturePack() = default;

    /**  set an additional color value multiplied into render copy operations. */
    void SetTextureColorMod(SDL_Colour color)
    {
        for (auto i = this->m_Animations.begin(); i != this->m_Animations.end(); i++)
        { (*i).second->SetTextureColorMod(color); }
    }

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
    std::map<ETextureType, std::unique_ptr<CAnimation>> m_Animations;
    CCoord<> m_TextureSize;
    bool m_IsCentered;
};

