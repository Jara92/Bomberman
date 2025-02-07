/**
 * @author Jaroslav Fikar
*/

#pragma once

#include <memory>
#include <map>
#include <vector>
#include <algorithm>
#include "CRandom.h"
#include "Messages.h"
#include "enums/EGameStatus.h"
#include "blocks/CWall.h"
#include "blocks/CFire.h"
#include "blocks/CBomb.h"
#include "blocks/collectibles/CCollectible.h"
#include "movables/CEnemyDumb.h"
#include "movables/CEnemySmart.h"
#include "movables/CPlayer.h"

/** Game board contains gameobjects which are rendered in window. */
class CBoard
{
public:
    CBoard(CSettings &settings, std::vector<std::vector<CBlock *>> map,
           CCoord<unsigned int> boardSize, std::shared_ptr<CBlock> ground,
           std::shared_ptr<CTexturePack> bombTexturePack, std::shared_ptr<CTexturePack> fireTexturePack,
           unsigned int cellSize)
            : m_Map(std::move(map)), m_Settings(settings),
              m_BoardSize(boardSize), m_CellSize(cellSize), m_GroundObject(std::move(ground)),
              m_BombObjectTexturePack(std::move(bombTexturePack)), m_FireObjectTexturePack(std::move(fireTexturePack))
    {}

    ~CBoard();

    CBoard(const CBoard &other) = delete;

    CBoard &operator=(const CBoard &other) = delete;

    /**
     * Update all objects in the board.
     * @param deltaTime Deltatime
     */
    void Update(int deltaTime);

    void UpdatePhysicsEvents();

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
    bool IsPassable(CCoord<unsigned int> coord, const CMovable &movable) const;

    /**
     * Is this position totaly free?
     * @param coord Position
     * @return True - Totaly free
     */
    bool PositionFree(CCoord<unsigned int> coord);

    /**
     * Is area around players free?
     * @param coord Location.
     * @param playerSaveZone Players save zone.
     * @return True - Location free
     */
    bool PlayersAreaFree(CCoord<unsigned int> coord, double playerSaveZone);

    /**
     * Place bomb in game board.
     * @param player Bomb owner.
     * @return True - Success.
     */
    bool PlaceBomb(CPlayer *player);

    /**
     * Cause explosion in game board.
     * @param bomb Bomb to explode.
     */
    void CauseExplosion(CBomb *bomb)
    { this->m_BombsToExplode.insert(bomb); }

    /**
     * Trigger explosion in bombs location.
     * @param bomb Exploding bomb.
     * @param bombLocation Exploding bomb location.
     */
    void CreateExplosion(CBomb &bomb, CCoord<unsigned int> bombLocation);

    /**
     * Trigger explosion in one direction.
     * @param bombLocation Source bomb location.
     * @param direction Direction vector.
     * @param explosionRadius Explosion radius.
     * @param owner Fire owner. The owner receives a score for killed enemies.
     */
    void CreateExplosionWave(CCoord<unsigned int> bombLocation, CCoord<int> direction, unsigned int explosionRadius,
                             CPlayer *owner);

    void DestroyEveryDestructibleWall();

    /**
     * Remove all dynamically added objects. (Bombs, Enemies, Boosts, DestructibleWalls)
     * @param clearLevelObjects Remove boosts from the board?
     * @param collectibles Output vector to return every CCollectible objects which is in the board or attached to CWall.
     */
    void PrepareBoard(bool clearLevelObjects, std::vector<CCollectible *> &collectibles);

    /**
    * Get random location in the board.
    * @return Random location.
    */
    CCoord<unsigned int> GetRandomBoardLocation() const
    {
        // Return random location on the board.
        return CCoord<unsigned int>(CRandom::Random(0, this->m_BoardSize.m_X),
                                    CRandom::Random(0, this->m_BoardSize.m_Y));
    }

    /**
     * Get block from the map at given location.
     * @param location Location in 2D array.
     * @throws std::out_of_range When the location is out of bound.
     * @return CBlock at given location
     */
    CBlock *GetMapItem(CCoord<unsigned int> location) const;

    /**
     * Set block at given location.
     * @param block Block to be set.
     * @param location Location in 2D array.
     * @throws std::out_of_range When the location is out of bound.
     */
    void SetMapItem(CBlock *block, CCoord<unsigned int> location);

    CCoord<unsigned int> GetBoardSize() const
    { return this->m_BoardSize; }

    unsigned int GetCellSize() const
    { return this->m_CellSize; }

    /** Set players if there are none. */
    void SetPlayers(std::vector<CPlayer *> players)
    {
        if (this->m_Players.empty())
        {
            this->m_Players = std::move(players);
            this->m_Movables.insert(this->m_Movables.end(), this->m_Players.begin(), this->m_Players.end());
        }
    }

    std::vector<CPlayer *> m_Players;
    /** Game map saved as 2D array */
    std::vector<std::vector<CBlock *>> m_Map;
    std::vector<CMovable *> m_Movables;

    /** Game settings */
    CSettings &m_Settings;

    std::shared_ptr<CBlock> GetGroundObject() const
    { return this->m_GroundObject; }

protected:
    /** Size of game board. */
    CCoord<unsigned int> m_BoardSize;
    /** Size of one cell in pixels. */
    unsigned int m_CellSize;

    /** The set of bombs that will be detonated when "CBoard::Update ()" is called */
    std::set<CBomb *, std::less<> > m_BombsToExplode;

    /** Ground object template */
    std::shared_ptr<CBlock> m_GroundObject;

    /** Texture packs to be used as template. */
    std::shared_ptr<CTexturePack> m_BombObjectTexturePack, m_FireObjectTexturePack;
};
