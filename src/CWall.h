/**
 * @author Jaroslav Fikar
 * 
*/

#pragma once

#include "gameobjects/CBlock.h"
#include "gameobjects/collectibles/CCollectible.h"

class CWall : public CBlock
{
public:
    /**
    * Wall constructor.
    * @param texturePack Texture pack to be rendered.
    * @param isDestructible Is this wall destructible?
    */
    CWall(std::shared_ptr<CTexturePack> texturePack, bool isDestructible)
            : CBlock(std::move(texturePack)), m_IsDestructible(isDestructible), m_IsAlive(true), m_Collectible(nullptr)
    {}

    CWall(const CWall &other) = default;

    CWall &operator=(const CWall &other) = default;

    ~CWall() = default;

    /**
    * Try to destroy the wall.
    * @param distance Distance from the bomb.
    */
    bool TryDestroy(unsigned int distance);

    /**
     * Is this wall destructible?
     * @return True - is destructible.
     */
    bool IsDestructible()
    { return this->m_IsDestructible; }

    /**
     * Attach collectible object to this wall.
     * @param collectible Collectible object.
     */
    void AttachCollectible(CCollectible *collectible)
    {
        if (!this->m_Collectible && this->m_IsDestructible)
        { this->m_Collectible = collectible; }
    }

    /** Detach attached collectible object. */
    void DetachCollectible()
    { this->m_Collectible = nullptr; }

    /**
     * Has this wall already collectible object?
     * @return True - Has collectible object.
     */
    bool HasCollectible() const
    { return this->m_Collectible; }

    bool IsAlive() const
    { return this->m_IsAlive; }

protected:
    bool m_IsDestructible, m_IsAlive;
    CCollectible *m_Collectible;
};

