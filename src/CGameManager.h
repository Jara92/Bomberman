/**
 * @author Jaroslav Fikar
 * 
*/

#pragma once
#include <functional>
#include "CSDLInterface.h"
#include "CClock.h"
#include "CBoard.h"
#include "CLevelLoader.h"
#include "EGameStatus.h"
#include "CTimer.h"
#include "CScoreManager.h"

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
    CScoreManager m_ScoreManager;
    CCoord m_BoardOffset;
    CLevelLoader * m_LevelLoader;
    CGameClock m_Clock;
    EGameStatus m_GameStatus;
    unsigned int m_Level;
    int m_RemainingTime;
    CTimer m_GameEndDelay;
    EGameStatus m_NextGameStatus;
    CTimer m_GameStatusDelay;

    static constexpr int STARTING_TIME = 1000;//201000;
    static constexpr int GAME_STATUS_DELAY = 2000;

    void GlobalInput(const Uint8 * input);

    void NextRound();
    void RoundOver();
    void GameOver();
    void RoundInit();

    void SetStatus(EGameStatus newStatus);
    void UpdateStatus();

    void Draw() const;
    void DrawGame() const;
    void DrawRoundOver() const;
    void DrawNextRound() const;
    void DrawGameOver() const;
    void Update(int deltaTime);
    void UpdateEvents();
};

