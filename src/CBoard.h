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
#include "EGameStatus.h"

class CBoard
{
public:
    CBoard(CSettings * settings, std::vector<std::vector<CWall *>> map, std::vector<CPlayer *> players, CCoord boardSize, CGround *ground,
           std::shared_ptr<CTexturePack> bombTexturePack, std::shared_ptr<CTexturePack> fireTexturePack, int cellSize)
            : m_Players(std::move(players)), m_Map(std::move(map)), m_BoardSize(boardSize), m_CellSize(cellSize),
              m_GroundObject(ground), m_BombObjectTexturePack(std::move(bombTexturePack)),
              m_FireObjectTexturePack(std::move(fireTexturePack)), m_Settings(settings)
    {}

    ~CBoard();

    CBoard(const CBoard &other) = default;

    CBoard &operator=(const CBoard &other) = default; // todo check this

    /**
     * Update all objects in the board.
     * @param deltaTime Deltatime
     */
    void Update(int deltaTime);

    EGameStatus UpdatePhysics();

    /**
     * Draw all objects in the board.
     * @param interface Interface to be used.
     */
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
     * Is area around players free?
     * @param coord Position
     * @return True - Location free
     */
    bool PlayersAreaFree(CCoord coord);

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
    void CreateExplosionWave(CBomb * bomb, CCoord direction, unsigned int explosionRadius);

    /**
     * Delete fire from the map.
     * @param fire Fire to be removed.
     */
    void DestroyExplosion(CFire * fire);

    EGameStatus RoundOver(CPlayer * player);

    /**
     * Remove all dynamically added objects. (Bombs, Enemies, Boosts, DestructibleWalls)
     */
    void ClearBoard();

    CCoord GetBoardSize() const
    { return this->m_BoardSize; }

    /** Saved objects */
    std::vector<CPlayer *> m_Players;
    std::vector<CEnemy *> m_Enemies;
    std::map<CCoord, CCollectible *> m_Boosts;
    std::map<CCoord, CFire *> m_Fires;
    std::map<CCoord, CBomb *> m_Bombs;
    std::vector<std::vector<CWall *>> m_Map;

    /** Game settings */
    CSettings * m_Settings;

protected:
    /** Size of gameboard. */
    CCoord m_BoardSize;
    /** Size of one cell in pixels. */
    int m_CellSize;

    /** Ground object template */
    CGround *m_GroundObject;

    /** Texturepack templates. */
    std::shared_ptr<CTexturePack> m_BombObjectTexturePack;
    std::shared_ptr<CTexturePack> m_FireObjectTexturePack;

    /**
     * Is this direction free to place?
     * @param location Location
     * @param player Player
     * @param direction Direction vector.
     * @return True - Direction is free.
     */
    bool PlayerDirectionFree(CCoord location, CPlayer * player, CCoord direction);
};

