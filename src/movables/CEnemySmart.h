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

    /**
     * Enemy finds best way to target location.
     * @param board Game board.
     * @param location Target location.
     * @return New movement vector.
     */
    CCoord<> FindWayToLocation(const CBoard &board, CCoord<unsigned int> location);

    /**
     * Enemy follows the player.
     * @param board Game board.
     */
    bool FollowThePlayer(const CBoard &board);

    std::vector<CCoord<int>> m_PathToPlayer;
    std::vector<CCoord<int>> m_DirectionsToPlayer;

    std::vector<CCoord<int>> FindPathTo(const CBoard & board, CCoord<unsigned int> currentLocation,
                                        CCoord<unsigned int> targetLocation);

    void FindPathToRec(std::vector<std::vector<bool>> &map, int i, int j,
                       std::vector<CCoord<int>> &temp, std::vector<CCoord<int>> &list,
                       std::vector<CCoord<int>> &tempDirections,
                       std::vector<CCoord<int>> &directions, CCoord<unsigned int> targetLocation);
};

