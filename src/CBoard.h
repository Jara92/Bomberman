/**
 * @author Jaroslav Fikar
 * 
*/

#pragma once

#include <memory>
#include <map>
#include <vector>
#include <chrono>
#include <random>
#include "Messages.h"
#include "EGameStatus.h"
#include "CWall.h"
#include "gameobjects/CFire.h"
#include "gameobjects/CBomb.h"
#include "gameobjects/collectibles/CCollectible.h"
#include "gameobjects/movables/CEnemyDump.h"
#include "gameobjects/movables/CEnemySmart.h"
#include "gameobjects/movables/CPlayer.h"

/** Game board contains gameobjects which are rendered in window. */
class CBoard
{
public:
    CBoard(std::shared_ptr<CSettings> settings, std::vector<std::vector<CBlock *>> map, std::vector<CPlayer *> players,
           CCoord<unsigned int> boardSize, std::shared_ptr<CBlock> ground,
           std::shared_ptr<CTexturePack> bombTexturePack,
           std::shared_ptr<CTexturePack> fireTexturePack, unsigned int cellSize)
            : m_Players(std::move(players)), m_Map(std::move(map)), m_Settings(std::move(settings)),
              m_BoardSize(boardSize), m_CellSize(cellSize), m_GroundObject(std::move(ground)),
              m_BombObjectTexturePack(std::move(bombTexturePack)), m_FireObjectTexturePack(std::move(fireTexturePack))
    {}

    ~CBoard();

    CBoard(const CBoard &other) = delete;

    CBoard &operator=(const CBoard &other) = delete; // todo check this

    /**
     * Update all objects in the board.
     * @param deltaTime Deltatime
     */
    void Update(int deltaTime);


    void UpdatePhysicEvents();

    /**
     * Draw all objects in the board.
     * @param interface Interface to be used.
     * @param offset Board offset in window.
     */
    void Draw(CSDLInterface &interface, CCoord<> offset = CCoord<>(0, 0));

    /**
     * Is this coord passable for the player?
     * @param coord Location.
     * @param movable Movable object.
     * @return True if is passable.
     */
    bool IsPassable(CCoord<unsigned int> coord, const CMovable *movable);

    /**
     * Is this position totaly free?
     * @param coord Position
     * @return True - Totaly free
     */
    bool PositionFree(CCoord<unsigned int> coord);

    /**
     * Is area around players free?
     * @param coord Position
     * @return True - Location free
     */
    bool PlayersAreaFree(CCoord<unsigned int> coord);

    /**
     * Place bomb in game board.
     * @param player Bomb owner.
     * @return True - Success.
     */
    bool PlaceBomb(CPlayer *player);

    /**
     * Detonate bombs owned by player
     * @param player Player
     */
    void DetonateBombs(const CPlayer *player);

    /**
     * Cause explosion in game board.
     * @param bomb Bomb to explode.
     */
    void CauseExplosion(CBomb * bomb)
    {this->m_BombsToExplode.insert(bomb);    }
    /**
     * Trigger explosion in bombs location.
     * @param bomb Exploding bomb.
     */
    void CreateExplosion(CBomb *bomb, CCoord<unsigned int> bombLocation);

    /**
     * Trigger explosion in one direction.
     * @param bombLocation Source bomb location.
     * @param direction Direction vector.
     * @param explosionRadius Explosion radius.
     */
    void CreateExplosionWave(CCoord<unsigned int> bombLocation, CCoord<int> direction, unsigned int explosionRadius);

    /**
     * Delete collectible from the map.
     * @param collectible Collectible to be removed.
     */
    void DestroyCollectible(CCollectible *collectible);

    /**
     * Remove all dynamically added objects. (Bombs, Enemies, Boosts, DestructibleWalls)
     * @param clearLevelObjects Remove boosts from the board?
     */
    void ClearBoard(bool clearLevelObjects = true);

    /**
    * Get random location in the board.
    * @return Random location.
    */
    CCoord<unsigned int> GetRandomBoardLocation() const
    {
        // Random number generator.
        unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
        std::default_random_engine random(seed);

        // Return random location on the board.
        return CCoord<unsigned int>((random() % (this->m_BoardSize.m_X)), (random() % (this->m_BoardSize.m_Y)));
    }

    CCoord<unsigned int> GetBoardSize() const
    { return this->m_BoardSize; }

    unsigned int GetCellSize() const
    { return this->m_CellSize; }

    /** Saved objects */
    std::vector<CPlayer *> m_Players;
    std::vector<CEnemy *> m_Enemies;
    std::map<CCoord<unsigned int>, CCollectible *> m_Collectibles;
    std::map<CCoord<unsigned int>, CBomb *> m_Bombs;
    std::vector<std::vector<CBlock *>> m_Map;
    std::vector<CGameObject *> m_GameObjects;

    std::set<CBomb*,std::less<> > m_BombsToExplode;

    /** Game settings */
    std::shared_ptr<CSettings> m_Settings;

    std::shared_ptr<CBlock> GetGroundObject() const
    { return this->m_GroundObject; }

protected:
    /** Size of game board. */
    CCoord<unsigned int> m_BoardSize;
    /** Size of one cell in pixels. */
    unsigned int m_CellSize;
    static constexpr unsigned int PLAYER_SAVE_ZONE = 3;

    /** Ground object template */
    std::shared_ptr<CBlock> m_GroundObject;

    /** Texture packs to be used as template. */
    std::shared_ptr<CTexturePack> m_BombObjectTexturePack, m_FireObjectTexturePack;

    /**
     * Is this direction free to place?
     * @param location Location
     * @param player Player
     * @param direction Direction vector.
     * @return True - Direction is free.
     */
    bool PlayerDirectionFree(CCoord<unsigned int> location, CPlayer *player, CCoord<int> direction);
};
