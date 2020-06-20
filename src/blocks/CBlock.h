/**
 * @author Jaroslav Fikar
*/

#pragma once

#include <memory>
#include "../CTimer.h"
#include "../CBody.h"
#include "../movables/CMovable.h"
#include "../CSDLInterface.h"
#include "../CTexturePack.h"
#include "../movables/CPlayer.h"
#include "../movables/CEnemy.h"

class CBoard;

class CCollectible;

class CBlock
{
public:
    /**
    * Game object contructor
    * @param texturePack Texturepack to be rendered.
    * @param size Object size.
    * @param isPassable Is this object passable for moving objects?
    * @param isDangerous Is this object dangerous for other objects?
    */
    CBlock(std::shared_ptr<CTexturePack> texturePack, CCoord<> size, bool isPassable, bool isExplodable,
           bool isDangerous)
            : m_Body(std::move(texturePack), 100), m_Size(size), m_IsAlive(true), m_IsDestroyed(false),
              m_IsPassable(isPassable), m_IsExplodable(isExplodable), m_IsDangerous(isDangerous)
    {}

    CBlock(const CBlock &other) = default;

    CBlock &operator=(const CBlock &other) = default;

    virtual ~CBlock() = default;

    /**
    * Try to destroy the block.
    * @param distance Distance from the bomb.
     * @return True - Successfully destroyed.
    */
    virtual bool TryExplode(unsigned int distance)
    { return false; }

    /**
     * Is this object passable for movement?
     * @param thisLocation This block location.
     * @param movable Movable to pass.
     * @return True - Block is passable for the movable.
     */
    virtual bool IsPassable(CCoord<unsigned int> thisLocation, const CMovable &movable) const
    { return (this->IsColliding(thisLocation, movable) ? this->m_IsPassable : true); }

    /** Hadnle collision with player. */
    virtual void CollisionWith(CCoord<unsigned int> thisLocation, CPlayer &player)
    {}

    /** Handle collision with enemy. */
    virtual void CollisionWith(CCoord<unsigned int> thisLocation, CEnemy &enemy)
    {}

    /**
    * Updates object state using deltatime.
    * @param board Game board
    * @param deltaTime DeltaTime
    */
    virtual void Update(CBoard &board, int deltaTime)
    { this->m_Body.Update(board, deltaTime); }

    /**
     * Draw block.
     * @param interface Interface to be used.
     * @param cellSize Game board cell size.
     * @param location Block location.
     * @param offset Drawing offset.
     */
    virtual void
    Draw(CSDLInterface &interface, int cellSize, CCoord<> location, CCoord<> offset = CCoord<>(0, 0)) const
    { this->m_Body.Draw(interface, cellSize, location, this->m_Size, offset); }

    /**
    * Prepare block for next level.
    * @param board Game board.
    * @param clearLevelObjects Objects associated with the level will be deleted.
    */
    virtual void NextLevel(CBoard &board, bool clearLevelObjects)
    {}

    /**
     * Attach collectible object to this wall.
     * @param collectible Collectible object.
     */
    virtual void AttachCollectible(CCollectible *collectible)
    {}

    /**
    * Are these objects colliding?
     * @param thisLocation Location of this object in game board.
    * @param other Other object
    */
    bool IsColliding(CCoord<unsigned int> thisLocation, const CMovable &other) const
    { return this->m_Body.IsColliding(thisLocation.ToDouble(), this->m_Size, other.GetLocation(), other.GetSize()); }

    /**
     * Has this object attached collectible object?
     * @return True - Has collectible object.
     */
    virtual bool HasCollectible() const
    { return false; }

    virtual CCollectible *GetCollectible()
    { return nullptr; }

    bool IsAlive() const
    { return this->m_IsAlive; }

    bool IsDestroyed() const
    { return this->m_IsDestroyed; }

    bool IsExplodeable() const
    { return this->m_IsExplodable; }

    bool IsDangerous() const
    { return this->m_IsDangerous; }

    void Kill()
    { this->m_IsAlive = false; }

protected:
    CBody m_Body;
    CCoord<> m_Size;
    bool m_IsAlive, m_IsDestroyed, m_IsPassable, m_IsExplodable, m_IsDangerous;
};

