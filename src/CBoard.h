/**
 * @author Jaroslav Fikar
 * 
*/

#pragma once

#include <memory>
#include <map>
#include <vector>
#include <chrono>
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

/**
 * Game board contains gameobjects which are rendered in window.
 */
class CBoard
{
public:
    CBoard(std::shared_ptr<CSettings> settings, std::vector<std::vector<CWall *>> map, std::vector<CPlayer *> players, CCoord boardSize,
           std::shared_ptr<CGround> ground, std::shared_ptr<CTexturePack> bombTexturePack,
           std::shared_ptr<CTexturePack> fireTexturePack, unsigned int cellSize)
            : m_Players(std::move(players)), m_Map(std::move(map)), m_Settings(std::move(settings)), m_BoardSize(boardSize),
              m_CellSize(cellSize), m_GroundObject(std::move(ground)),
              m_BombObjectTexturePack(std::move(bombTexturePack)),
              m_FireObjectTexturePack(std::move(fireTexturePack))
    {}


    ~CBoard();

    CBoard(const CBoard &other) = default;

    CBoard &operator=(const CBoard &other) = default; // todo check this

    /**
     * Update all objects in the board.
     * @param deltaTime Deltatime
     */
    void Update(int deltaTime);

    void UpdatePhysics();

    /**
     * Draw all objects in the board.
     * @param interface Interface to be used.
     */
    void Draw(CSDLInterface *interface, CCoord offset = CCoord(0, 0));

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
    void CreateExplosionWave(CBomb *bomb, CCoord direction, unsigned int explosionRadius);

    /**
     * Delete fire from the map.
     * @param fire Fire to be removed.
     */
    void DestroyExplosion(CFire *fire);

    /**
     * Delete collectible from the map.
     * @param collectible Collectible to be removed.
     */
    void DestroyCollectible(CCollectible *collectible);

    /**
     * Remove all dynamically added objects. (Bombs, Enemies, Boosts, DestructibleWalls)
     * @param clearBoosts Remove boosts from the board?
     */
    void ClearBoard(bool clearBoosts = true);

    CCoord GetBoardSize() const
    { return this->m_BoardSize; }

    unsigned int GetCellSize() const
    { return this->m_CellSize; }

    /** Saved objects */
    std::vector<CPlayer *> m_Players;
    std::vector<CEnemy *> m_Enemies;
    std::map<CCoord, CCollectible *> m_Collectibles;
    std::map<CCoord, CFire *> m_Fires;
    std::map<CCoord, CBomb *> m_Bombs;
    std::vector<std::vector<CWall *>> m_Map;

    /** Game settings */
    std::shared_ptr<CSettings> m_Settings;

    std::shared_ptr<CGround> GetGroundObject() const
    { return this->m_GroundObject; }

protected:
    /** Size of gameboard. */
    CCoord m_BoardSize;
    /** Size of one cell in pixels. */
    unsigned int m_CellSize;

    /** Ground object template */
    std::shared_ptr<CGround> m_GroundObject;

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
    bool PlayerDirectionFree(CCoord location, CPlayer *player, CCoord direction);
};

