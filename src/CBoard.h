/**
 * @author Jaroslav Fikar
 * 
*/

#pragma once

#include <memory>
#include <map>
#include <vector>
#include "Messages.h"
#include "CCoord.h"
#include "gameobjects/CGameObject.h"
#include "gameobjects/CGround.h"
#include "gameobjects/CWall.h"
#include "gameobjects/collectibles/CCollectible.h"
#include "gameobjects/CFire.h"
#include "gameobjects/movables/CEnemy.h"
#include "gameobjects/CBomb.h"
#include "gameobjects/movables/CPlayer.h"

class CBoard
{
public:
    CBoard(std::vector<std::vector<CWall *>> map, std::vector<CPlayer *> players, CCoord boardSize, CGround *ground,
           std::shared_ptr<CTexturePack> bombTexturePack, std::shared_ptr<CTexturePack> fireTexturePack, int cellSize)
            : m_Players(std::move(players)), m_Map(std::move(map)), m_BoardSize(boardSize), m_CellSize(cellSize),
              m_GroundObject(ground), m_BombObjectTexturePack(std::move(bombTexturePack)),
              m_FireObjectTexturePack(std::move(fireTexturePack))
    {}

    ~CBoard();

    CBoard(const CBoard &other) = delete;

    CBoard &operator=(const CBoard &other) = delete;

    void Update(int deltaTime);

    void UpdatePhysics();

    void Draw(CSDLInterface *interface);

    /**
     * Is this coord passable for the player?
     * @param coord Location
     * @param player Player
     * @return True if is passable.
     */
    bool IsPassable(CCoord coord, const CPlayer *player);

    /**
     * Is this position totaly free?
     * @param coord Position
     * @return True - Totaly free
     */
    bool PositionFree(CCoord coord);

    /**
     * Place bomb in game board.
     * @param player Bomb owner.
     */
    void PlaceBomb(CPlayer *player);

    /**
     * Detonate bombs owned by player
     * @param player Player
     */
    void DetonateBombs(const CPlayer *player);

    /**
     * Trigger explosion in bombs location.
     * @param bomb Exploding bomb.
     */
    void CreateExplosion(CBomb *bomb);

    /**
     * Trigger explosion in one direction.
     * @param location Explosion location.
     * @param direction Direction vector.
     * @param explosionRadius Explosion radius.
     */
    void CreateExplosionWave(CCoord location, CCoord direction, unsigned int explosionRadius);

    void DestroyExplosion(CFire * fire);

    std::vector<CPlayer *> m_Players;
    std::vector<CEnemy *> m_Enemies;
    std::map<CCoord, CCollectible *> m_Boosts;
    std::map<CCoord, CFire *> m_Fires;
    std::map<CCoord, CBomb *> m_Bombs;
    std::vector<std::vector<CWall *>> m_Map;

    CCoord GetBoardSize() const
    { return this->m_BoardSize; }

    /**
     * Remove all dynamically added objects. (Bombs, Enemies, Boosts, DestructibleWalls)
     */
    void ClearBoard();

protected:
    CCoord m_BoardSize;
    int m_CellSize;

    /** Ground object template */
    CGround *m_GroundObject;

    /** Texturepack templates. */
    std::shared_ptr<CTexturePack> m_BombObjectTexturePack;
    std::shared_ptr<CTexturePack> m_FireObjectTexturePack;
};

