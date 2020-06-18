/**
 * @author Jaroslav Fikar
*/

#pragma once

#include "../CBlock.h"
#include "../../movables/CPlayer.h"

class CCollectible : public CBlock
{
public:
    /**
    * Collectible object constructor.
    * @param texturePack Texture pack to be rendered.
    * @param size Object size.
    * @param scoreBonus Bonus to be claimed by collector.
    * @param duration Collectible duration in seconds. Set 0 for unlimited duration.
    */
    CCollectible(std::shared_ptr<CTexturePack> texturePack, CCoord<> size = CCoord<>(1, 1), size_t scoreBonus = 0,
                 int duration = 0)
            : CBlock(std::move(texturePack), size, true), m_Duration(duration), m_IsVisible(false),
              m_IsTriggered(false), m_ScoreBonus(scoreBonus), m_TargetPlayer(nullptr)
    {}

    CCollectible(const CCollectible &other) = default;

    CCollectible &operator=(const CCollectible &other) = default;

    virtual ~CCollectible() = default;

    virtual void Update(CBoard &board, int deltaTime) override
    {
        CBlock::Update(board, deltaTime);
        if (this->m_IsAlive && this->m_IsTriggered && this->m_TargetPlayer)
        { this->Apply(board, *(this->m_TargetPlayer)); }
    }

    virtual void
    Draw(CSDLInterface &interface, int cellSize, CCoord<> location, CCoord<> offset = CCoord<>(0, 0)) const override
    {
        // Render collectible only when this object is visible.
        if (this->m_IsVisible)
        { CBlock::Draw(interface, cellSize, location, offset); }
    }

    virtual void NextLevel(CBoard &board, bool clearLevelObjects) override;

    /**
     * Apply collectible on the player.
     * @param board Game board.
     * @param player Target player
     */
    virtual void Apply(const CBoard & board, CPlayer &player) = 0;

    /**
     * Handle collision with player.
     * @param thisLocation This block location.
     * @param player The player.
     */
    virtual void CollisionWith(CCoord<unsigned int> thisLocation, CPlayer &player) override
    {
        if (this->IsColliding(thisLocation, player))
        {
            this->m_IsTriggered = true;
            this->m_TargetPlayer = &player;
        }
    }

    /** Make collectible object visible */
    void MakeVisible()
    { this->m_IsVisible = true; }

    virtual bool HasCollectible() const
    { return true; }

    virtual CCollectible *GetCollectible()
    { return this; }

    virtual bool IsExplodeable() const override
    { return false; }

protected:
    int m_Duration;
    bool m_IsVisible, m_IsTriggered;
    size_t m_ScoreBonus;
    CPlayer *m_TargetPlayer;
};



