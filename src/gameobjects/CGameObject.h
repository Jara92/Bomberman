/**
 * @author Jaroslav Fikar
 * 
*/

#pragma once

#include <memory>
#include "../CTexturePack.h"

class CBoard;

/**
 * Represents basic gameobject which has location and texturepack.
 */
class CGameObject
{
public:
    /**
    * Game object contructor.
    * @param texturePack Texturepack to be rendered.
    * @param size Object size.
    * @param location Starting location.
    * @param isPassable Is this object passable for movable objects?
    */
    explicit CGameObject(std::shared_ptr<CTexturePack> texturePack, CCoord <> size = CCoord<>(1, 1),
                         CCoord <>location = CCoord<>(0, 0), bool isPassable = false)
            : m_TexturePack(std::move(texturePack)), m_ActualTexture(ETextureType::TEXTURE_FRONT),
              m_IsPassable(isPassable), m_IsAlive(true), m_Size(size), m_Location(location), m_AnimationIndex(0),
              m_AnimationUpdateInterval(100),
              m_AnimationTimer(0)
    {}

    CGameObject(const CGameObject &other) = default;

    CGameObject &operator=(const CGameObject &other) = default;

    virtual ~CGameObject() = default;

    /**
     * Is this object alive?
     * @return True is the object is alive.
     */
    bool IsAlive() const
    { return this->m_IsAlive; }

    /**
     * Is this object passable?
    * @return True is the object is passable.
    */
    bool IsPassable() const
    { return this->m_IsPassable; }

    CCoord <>GetLocation() const
    { return this->m_Location; }

    CCoord <>GetSize() const
    { return this->m_Size; }

    /**
    * Updates object state using deltatime.
    * @param board Game board
    * @param deltaTime DeltaTime
    */
    virtual void Update(CBoard *board, int deltaTime)
    { this->Animate(deltaTime); }

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
     * Draw the gameobject
     * @param interface Interface
     * @param cellSize Cellsize
     * @param location Target cell location
     * @param offset Texture global offset
     */
    virtual void Draw(CSDLInterface *interface, int cellSize, CCoord <>location, CCoord <> offset = CCoord<>(0, 0)) const;

    /**
     * Are these objects colliding?
     * @param other Other object
     */
    bool IsColiding(const CGameObject *other) const;

    void SetLocation(CCoord<> location)
    {this->m_Location = location;}

protected:
    /** Texturepack which is used for rendering. */
    std::shared_ptr<CTexturePack> m_TexturePack;
    /** Actual texture type to be rendered. */
    ETextureType m_ActualTexture;
    /** Is this object passable for other objects? */
    bool m_IsPassable;
    bool m_IsAlive;
    CCoord <>m_Size;
    CCoord <>m_Location;

    /* Mutable keyword is very useful here. Animation index is not important for CGameObject, because it
     * does not disrupt the internal structure of the object. It is just auxiliary variable.*/
    mutable unsigned int m_AnimationIndex;
    unsigned int m_AnimationUpdateInterval;
    unsigned int m_AnimationTimer;

    /**
    * Returns the texture to be rendered.
    * @return SDL_Texture * to be rendered. Nullptr if there is no texture (this should never happen).
    */
    SDL_Texture *GetTexture() const;
};

