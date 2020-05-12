/**
 * @author Jaroslav Fikar
 * 
*/

#pragma once

#include "../CGameObject.h"
#include "../CPlayer.h"

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
            : CGameObject(texturePack, true), m_Duration(duration), m_TargetPlayer(nullptr)
    {}

    CCollectible(const CCollectible &other) = default;

    CCollectible &operator=(const CCollectible &other) = delete;

    virtual ~CCollectible() = default;

    virtual void Update(CBoard *board, int deltaTime) override
    {}

    /**
     * Apply collectible on the player.
     * @param player Target player
     */
    virtual void Apply(CPlayer *player) = 0;

protected:
    int m_Duration;
    size_t m_ScoreBonus;
    CPlayer *m_TargetPlayer;

    /**
     * Deativate collectible.
     */
    virtual void Deactivate() = 0;
};

