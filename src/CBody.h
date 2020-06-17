/**
 * @author Jaroslav Fikar
 * 
*/

#pragma once

#include "CTexturePack.h"

class CBoard;

class CBody
{
public:
    CBody(std::shared_ptr<CTexturePack> texturePack, unsigned int animationUpdateInterval = 100)
            : m_TexturePack(std::move(texturePack)), m_ActualTexture(ETextureType::TEXTURE_FRONT), m_AnimationIndex(0),
              m_AnimationUpdateInterval(animationUpdateInterval), m_AnimationTimer(0)
    {}

    /**
    * Updates body state using deltatime.
    * @param board Game board
    * @param deltaTime DeltaTime
    */
    virtual void Update(CBoard &board, int deltaTime)
    { this->Animate(deltaTime); }

    /**
     * Draw block.
     * @param interface Interface to be used.
     * @param cellSize Game board cell size.
     * @param location Object location.
     * @param size Object size.
     * @param offset Drawing offset.
     */
    virtual void
    Draw(CSDLInterface &interface, int cellSize, CCoord<> location, CCoord<> size,
         CCoord<> offset = CCoord<>(0, 0)) const;

    /**
    * Are these objects colliding?
     * @param aLocation First object location.
     * @param aSize First object size.
     * @param bLocation Second object location.
     * @param bSize Second object size.
    */
    bool IsColliding(CCoord<> aLocation, CCoord<> aSize, CCoord<> bLocation, CCoord<> bSize) const;

    /** NextLevel the object and prepare for a next round. */
    void Reset()
    {
        this->m_AnimationIndex = this->m_AnimationTimer = 0;
        this->m_ActualTexture = ETextureType::TEXTURE_FRONT;
    }

    void SetActualTextureType(ETextureType newTextureType)
    {this->m_ActualTexture = newTextureType;}

protected:
    /** Texturepack which is used for rendering. */
    std::shared_ptr<CTexturePack> m_TexturePack;
    /** Actual texture type to be rendered. */
    ETextureType m_ActualTexture;
    /* Mutable keyword is very useful here. Animation index is not important for CGameObject, because it
    * does not disrupt the internal structure of the object. It is just auxiliary variable. */
    mutable unsigned int m_AnimationIndex;
    unsigned int m_AnimationUpdateInterval;
    unsigned int m_AnimationTimer;

    /**
    * Update animation state
    * @param deltaTime DeltaTime
    */
    virtual void Animate(int deltaTime)
    {
        this->m_AnimationTimer += deltaTime;
        if (this->m_AnimationTimer >= this->m_AnimationUpdateInterval)
        {
            this->m_AnimationIndex++;
            this->m_AnimationTimer = 0;
        }
    }

    /**
    * Returns the texture to be rendered.
    * @return SDL_Texture * to be rendered. Nullptr if there is no texture (this should never happen).
    */
    SDL_Texture *GetTexture() const
    {
        SDL_Texture *texture = this->m_TexturePack.get()->GetTexture(this->m_ActualTexture, &(this->m_AnimationIndex));
        return texture;
    }
};

