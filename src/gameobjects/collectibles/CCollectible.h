/**
 * @author Jaroslav Fikar
 * 
*/

#pragma once

#include "../CGameObject.h"
#include "../movables/CPlayer.h"

class CCollectible : public CGameObject
{
public:
    /**
    * Collectible object contructor
    * @param textures Texturepack to be rendered.
    * @param scoreBonus Bonus to be claimed by collector.
    * @param duration Collectible duration in seconds. Set 0 for unlimited duration.
    */
    explicit CCollectible(std::shared_ptr<CTexturePack> texturePack, size_t scoreBonus = 0, int duration = 0)
            : CGameObject(texturePack, true), m_Duration(duration), m_IsVisible(false), m_ScoreBonus(scoreBonus),
              m_TargetPlayer(nullptr)
    {}

    CCollectible(const CCollectible &other) = default;

    CCollectible &operator=(const CCollectible &other) = delete;

    virtual ~CCollectible() = default;

    virtual void Update(CBoard *board, int deltaTime) override = 0;

    /**
     * Apply collectible on the player.
     * @param player Target player
     */
    virtual void Apply(CPlayer *player) = 0;

    /**
     * Make collectible object visible
     */
    void MakeVisible()
    { this->m_IsVisible = true; }

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

