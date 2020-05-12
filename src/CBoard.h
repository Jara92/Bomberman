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
#include "gameobjects/CWall.h"
#include "gameobjects/collectibles/CCollectible.h"
#include "gameobjects/CFire.h"
#include "gameobjects/CEnemy.h"
#include "gameobjects/CBomb.h"
#include "gameobjects/CPlayer.h"

class CBoard
{
public:
    CBoard(CGameObject ***map, std::vector<CPlayer*> players, CCoord boardSize, int cellSize)
            :m_Players(std::move(players)),  m_Map(map), m_BoardSize(boardSize), m_CellSize(cellSize)
    {}

    ~CBoard();

    CBoard(const CBoard &other) = delete;

    CBoard &operator=(const CBoard &other) = delete;

    void Update(int deltaTime);

    void Draw(CSDLInterface * interface);

    /**
     * Is this coord passable?
     * @param coord
     * @return
     */
    bool IsPassable(CCoord coord, bool wallPass, bool bombPass, bool firePass);

    std::vector<CPlayer *> m_Players;
    std::vector<CEnemy *> m_Enemies;
    std::map<CCoord, CCollectible *> m_Boosts;
    std::map<CCoord, CFire *> m_Fires;
    std::map<CCoord, CBomb *> m_Bombs;

protected:
    CGameObject ***m_Map;
    CCoord m_BoardSize;
    int m_CellSize;
};

