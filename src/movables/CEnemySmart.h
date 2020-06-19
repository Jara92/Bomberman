/**
 * @author Jaroslav Fikar
*/

#pragma once

#include <queue>
#include "CEnemy.h"
#include "CPlayer.h"
#include "../blocks/collectibles/CCollectible.h"

class CEnemySmart : public CEnemy
{
public:
    /**
    * CEnemySmart contructor.
    * @param texturePack Texturepack to be rendered.
    * @param location Starting location. (Must be passable)
    * @param size Object size.
    * @param score Score to be claimed.
    * @param speed Enemy speed.
    * @param wallPass Can this Enemy walk through destructible walls?
    * @param lives How many lives doest this monster have?
    */
    explicit CEnemySmart(std::shared_ptr<CTexturePack> texturePack, CCoord<> location, CCoord<> size = CCoord<>(1, 1),
                         int score = 0, double speed = 0.005, bool wallPass = false, int lives = 1)
            : CEnemy(std::move(texturePack), location, size, score, speed, wallPass, lives, 1),
              m_PersecutedPlayer(nullptr)
    {}

    CEnemySmart(const CEnemySmart &other) = default;

    CEnemySmart &operator=(const CEnemySmart &other) = default;

    virtual ~CEnemySmart() = default;

    virtual void Update(CBoard &board, int deltaTime) override;

protected:
    const CPlayer *m_PersecutedPlayer;

    virtual void UpdateMovementMode() override;

    virtual void Move(const CBoard &board, int deltaTime) override;
};

