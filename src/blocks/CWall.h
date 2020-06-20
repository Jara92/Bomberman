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
    * @param isExplodable Is this wall destructible?
    */
    CWall(std::shared_ptr<CTexturePack> texturePack, bool isExplodable)
            : CBlock(std::move(texturePack), texturePack->GetTextureSize(), false, isExplodable, false),
              m_Collectible(nullptr)
    {}

    CWall(const CWall &other) = default;

    CWall &operator=(const CWall &other) = default;

    ~CWall() = default;

    virtual void NextLevel(CBoard &board, bool clearLevelObjects) override
    {
        if (this->m_IsExplodable)
        { this->m_IsDestroyed = true; }
    }

    virtual bool IsPassable(CCoord<unsigned int> thisLocation, const CMovable &movable) const override;

    virtual bool TryExplode(unsigned int distance) override;

    virtual void AttachCollectible(CCollectible *collectible) override
    {
        if (!this->m_Collectible && this->m_IsExplodable)
        { this->m_Collectible = collectible; }
    }

    virtual bool HasCollectible() const override
    { return (this->m_Collectible); }

    virtual CCollectible *GetCollectible() override
    { return this->m_Collectible; }


protected:
    CCollectible *m_Collectible;
};

