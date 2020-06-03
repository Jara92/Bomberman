/**
 * @author Jaroslav Fikar
 * 
*/

#pragma once

#include "CSDLInterface.h"
#include "CClock.h"
#include "CBoard.h"
#include "CLevelLoader.h"
#include "EGameStatus.h"

class CGameManager
{
public:
    CGameManager(CSDLInterface *interface);
    ~CGameManager();
    CGameManager (const CGameManager & other) = delete;
    CGameManager & operator = (const CGameManager & other) = delete;

    void Init();
    void Run();

protected:
    CSDLInterface * m_Interface;
    CBoard * m_Board;
    CCoord m_BoardOffset;
    CLevelLoader * m_LevelLoader;
    CGameClock m_Clock;
    bool m_GameIsRunning;
    EGameStatus m_GameStatus;
    unsigned int m_Level;
    int m_RemainingTime;
    int m_WaitingTime;

    static constexpr int STARTING_TIME = 201000;

    unsigned int Draw() const;
    unsigned int DrawGame() const;
    unsigned int DrawRoundOver() const;
    unsigned int DrawNextRound() const;
    unsigned int DrawGameOver() const;
    void Update(int deltaTime);
    void UpdateGameStatus();
};

