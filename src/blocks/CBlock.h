/**
 * @author Jaroslav Fikar
 * 
*/

#pragma once

#include <memory>
#include "../gameobjects/CGameObject.h"
#include "../CSDLInterface.h"
#include "../CTexturePack.h"
#include "../gameobjects/collectibles/CCollectible.h"
#include "../gameobjects/movables/CEnemy.h"

class CBoard;

class CBlock
{
public:
    /**
    * Game object contructor
    * @param texturePack Texturepack to be rendered.
     * @param isPassable Is this object passable for moving objects?
    * @param size Object size.
    */
    CBlock(std::shared_ptr<CTexturePack> texturePack, bool isPassable = false, CCoord<> size = {1,1})
    : m_TexturePack(std::move(texturePack)), m_Size(size), m_IsAlive(true),  m_IsPassable(isPassable), m_AnimationIndex(0),
    m_AnimationUpdateInterval(100), m_AnimationTimer(0)
    {}

    CBlock(const CBlock &other) = default;

    CBlock &operator=(const CBlock &other) = default;

    virtual ~CBlock() = default;

    /**
    * Try to destroy the wall.
    * @param distance Distance from the bomb.
    */
    virtual bool TryDestroy(unsigned int distance)
    {return false;}

    /**
     * Is this object passable for movement?
     * @param movable Movable object.
     * @return
     */
    virtual bool IsPassable(CCoord<unsigned int> thisLocation, const CMovable & movable) const;

    /**
    * Are these objects colliding?
     * @param thisLocation Location of this object in game board.
    * @param other Other object
    */
    bool IsColliding(CCoord<unsigned int> thisLocation, const CGameObject &other) const;

    virtual void PlayerCollision(CCoord<unsigned int> thisLocation, CPlayer & player){}

    virtual void EnemyCollision(CCoord<unsigned int> thisLocation, CEnemy & enemy){}

    /**
    * Updates object state using deltatime.
    * @param board Game board
    * @param deltaTime DeltaTime
    */
    virtual void Update(CBoard &board, int deltaTime)
    {this->Animate(deltaTime);}

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
        SDL_Texture *texture = this->m_TexturePack.get()->GetTexture(ETextureType ::TEXTURE_FRONT, &(this->m_AnimationIndex));
        return texture;
    }

    /**
     * Draw block.
     * @param interface Interface to be used.
     * @param cellSize Game board cell size.
     * @param location Block location.
     * @param offset Drawing offset.
     */
    void Draw(CSDLInterface &interface, int cellSize, CCoord<> location, CCoord<> offset = CCoord<>(0, 0));

    /**
     * Is this wall destructible?
    * @return True - is destructible.
    */
    virtual bool IsDestructible() const
    { return false; }

    /**
     * Attach collectible object to this wall.
     * @param collectible Collectible object.
     */
    virtual void AttachCollectible(CCollectible *collectible)
    {    }

    /**
     * Has this wall already collectible object?
     * @return True - Has collectible object.
     */
    virtual bool HasCollectible() const
    { return false; }

    bool IsAlive() const
    {return this->m_IsAlive;}

    void Kill()
    {this->m_IsAlive = false;}

protected:
    std::shared_ptr<CTexturePack> m_TexturePack;
    CCoord<> m_Size;
    bool m_IsAlive, m_IsPassable;

    /* Mutable keyword is very useful here. Animation index is not important for CGameObject, because it
 * does not disrupt the internal structure of the object. It is just auxiliary variable.*/
    mutable unsigned int m_AnimationIndex;
    unsigned int m_AnimationUpdateInterval;
    unsigned int m_AnimationTimer;
};

