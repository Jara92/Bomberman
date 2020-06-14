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
    * Collectible object contructor
    * @param texturePack Texturepack to be rendered.
    * @param location Object location.
    * @param size Object size.
    * @param scoreBonus Bonus to be claimed by collector.
    * @param duration Collectible duration in seconds. Set 0 for unlimited duration.
    */
    CCollectible(std::shared_ptr<CTexturePack> texturePack, CCoord<> size = CCoord<>(1, 1), size_t scoreBonus = 0,
                 int duration = 0)
            : CBlock(std::move(texturePack), true, size), m_Duration(duration), m_IsVisible(false),
              m_ScoreBonus(scoreBonus), m_TargetPlayer(nullptr)
    {}

    CCollectible(const CCollectible &other) = default;

    CCollectible &operator=(const CCollectible &other) = default;

    virtual ~CCollectible() = default;

    virtual void Update(CBoard &board, int deltaTime) override = 0;

    virtual void Draw(CSDLInterface &interface, int cellSize, CCoord<> location,
                      CCoord<> offset = CCoord<>(0, 0)) const override
    {
        // Render collectible only when this object is visible.
        if (this->m_IsVisible)
        { CBlock::Draw(interface, cellSize, location, offset); }
    }

    /**
     * Apply collectible on the player.
     * @param player Target player
     */
    virtual void Apply(CPlayer *player) = 0;

    virtual void Reset(CBoard &board);

    virtual void CollisionWithPlayer(CPlayer &player)
    { this->Apply(&player); }

    /**
     * Make collectible object visible
     */
    void MakeVisible()
    { this->m_IsVisible = true; }

    /**
     * Make collectible object invisible again.
     */
    void MakeInvisible()
    { this->m_IsVisible = false; }

    /**
     * Is this collectible object visible?
     * @return True - Is visible; False - Is invisible
     */
    bool IsVisible() const
    { return this->m_IsVisible; }

protected:
    int m_Duration;
    bool m_IsVisible;
    size_t m_ScoreBonus;
    CPlayer *m_TargetPlayer;
};



