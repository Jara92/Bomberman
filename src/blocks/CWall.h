/**
 * @author Jaroslav Fikar
 * 
*/

#pragma once

#include "CBlock.h"
#include "collectibles/CCollectible.h"

class CWall : public CBlock
{
public:
    /**
    * Wall constructor.
    * @param texturePack Texture pack to be rendered.
    * @param isDestructible Is this wall destructible?
    */
    CWall(std::shared_ptr<CTexturePack> texturePack, bool isDestructible)
            : CBlock(std::move(texturePack), false), m_IsDestructible(isDestructible), m_Collectible(nullptr)
    {}

    CWall(const CWall &other) = default;

    CWall &operator=(const CWall &other) = default;

    ~CWall() = default;

    virtual bool IsPassable(CCoord<unsigned int> thisLocation, const CMovable & movable) const override ;

    virtual bool TryDestroy(unsigned int distance) override;

    virtual bool IsDestructible() const override
    { return this->m_IsDestructible; }

    virtual void AttachCollectible(CCollectible *collectible) override
    {
        if (!this->m_Collectible && this->m_IsDestructible)
        { this->m_Collectible = collectible; }
    }

    virtual bool HasCollectible() const override
    { return (this->m_Collectible); }

    virtual CCollectible *GetCollectible() override
    { return this->m_Collectible; }


protected:
    bool m_IsDestructible;
    CCollectible *m_Collectible;
};
