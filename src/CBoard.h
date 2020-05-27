/**
 * @author Jaroslav Fikar
 * 
*/

#pragma once

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
    CBoard(CWall ***map, std::vector<CPlayer*> players, CCoord boardSize, CGround * ground, int cellSize)
            :m_Players(std::move(players)),  m_Map(map), m_BoardSize(boardSize), m_CellSize(cellSize), m_GroundObject(ground)
    {}

    ~CBoard();

    CBoard(const CBoard &other) = delete;

    CBoard &operator=(const CBoard &other) = delete;

    void Update(int deltaTime);

    void UpdatePhysics();

    void Draw(CSDLInterface * interface);

    /**
     * Is this coord passable for the player?
     * @param coord Location
     * @param player Player
     * @return True if is passable.
     */
    bool IsPassable(CCoord coord, const CPlayer * player);

    /**
     * Is this position totaly free?
     * @param coord Position
     * @return True - Totaly free
     */
    bool PositionFree(CCoord coord);

    /**
     * Detonate bombs owned by player
     * @param player Player
     */
    void DetonateBombs(CPlayer * player);

    std::vector<CPlayer *> m_Players;
    std::vector<CEnemy *> m_Enemies;
    std::map<CCoord, CCollectible *> m_Boosts;
    std::map<CCoord, CFire *> m_Fires;
    std::map<CCoord, CBomb *> m_Bombs;
    CWall ***m_Map;

    CCoord GetBoardSize() const
    {return this->m_BoardSize;}

    /**
     * Remove all dynamically added objects. (Bombs, Enemies, Boosts, DestructibleWalls)
     */
    void ClearBoard();

protected:
    CCoord m_BoardSize;
    int m_CellSize;

    CGround * m_GroundObject;
};

