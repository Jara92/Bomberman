/**
 * @author Jaroslav Fikar
 * 
*/

#pragma once

#include <memory>
#include "../CTexturePack.h"

class CBoard;

/**
 * Represents basic gameobject which has location and texture
 */
class CGameObject
{
public:
    /**
    * Game object contructor
    * @param textures Texturepack to be rendered.
     * @param isPassable Is this object passable for movable objects?
    */
    explicit CGameObject(std::shared_ptr<CTexturePack> texturePack, bool isPassable = false)
            : m_TexturePack(std::move(texturePack)), m_ActualTexture(ETextureType::TEXTURE_STATIC), m_IsPassable(isPassable), m_IsAlive(true)
    {}

    CGameObject(const CGameObject &other) = default;

    CGameObject &operator=(const CGameObject &other) = delete;

    virtual ~CGameObject() = default;

    /**
    * Returns the texture to be rendered.
    * @return SDL_Texture * to be rendered. Nullptr if there is no texture (this should never happen).
    */
    SDL_Texture *GetTexture() const
    { return this->m_TexturePack.get()->GetTexture(this->m_ActualTexture); }

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

    /**
    * Updates object state using deltatime.
    * @param board Game board
    * @param deltaTime DeltaTime
    */
    virtual void Update(CBoard * board, int deltaTime) = 0;

    virtual void Draw(CSDLInterface * interface, CCoord location, int cellSize,  CCoord offset = CCoord(0, 0)) const;

protected:
    std::shared_ptr<CTexturePack> m_TexturePack;
    ETextureType m_ActualTexture;
    bool m_IsPassable;
    bool m_IsAlive;
};

