/**
 * @author Jaroslav Fikar
 * 
*/

#pragma once
#include <functional>
#include "CWindowManager.h"
#include "../CSDLInterface.h"
#include "../CGameClock.h"
#include "../CBoard.h"
#include "../CLevelLoader.h"
#include "../EGameStatus.h"
#include "../CTimer.h"
#include "../CScoreSaver.h"

class CGameManager : public CWindowManager
{
public:
    /**
     * Constructor.
     * @param interface Interface to be used.
     */
    explicit CGameManager(CSDLInterface *interface);
    virtual ~CGameManager() = default;
    CGameManager (const CGameManager & other) = delete;
    CGameManager & operator = (const CGameManager & other) = delete;

    /**
     * Run the game.
     */
    virtual EApplicationStatus Run() override ;

protected:
    std::shared_ptr<CBoard> m_Board;
    CScoreSaver m_ScoreManager;
    /** The board must be drawn shifted because of top menu. */
    CCoord m_BoardOffset;
    std::unique_ptr<CLevelLoader> m_LevelLoader;
    /** Current game state. */
    EGameStatus m_GameStatus;
    /** next game state which will be set when m_GameStatusDelay is done. */
    EGameStatus m_NextGameStatus;
    unsigned int m_Level;
    /** Timer which detects expiration of time. */
    CTimer m_GameEndDelay;
    /** Timer which updates game state updates a time delay. */
    CTimer m_GameStatusDelay;

    /**
     * The time a player has to complete the game.
     */
    static constexpr int STARTING_TIME = 200500;
    /**
     * Waiting time between loading scenes.
     */
    static constexpr int GAME_STATUS_DELAY = 2000;

    /**
     * Global input events.
     * @param input Keystate
     */
    void GlobalInput(const Uint8 * input);

    /**
     * Prepare board for next round.
     */
    void NextRound();

    /**
     * Reload current level.
     */
    void RoundOver();

    /**
     * Save top score and shut off the game.
     */
    void GameOver();

    /**
     * Fill game state with value of next game state and fill next game state with value of newStatus.
     * @param newStatus New game state.
     */
    void SetStatus(EGameStatus newStatus);

    /**
     * Fill game state with value of next game state.
     */
    void UpdateStatus();
    void KillAllPlayers();

    /**
     * Draw game by the game state.
     */
    virtual void Draw() const override ;
    void DrawGame() const;
    void DrawRoundOver() const;
    void DrawNextRound() const;
    void DrawGameOver() const;

    /**
     * Update game.
     * @param deltaTime Delta time.
     */
    virtual void Update(int deltaTime) override ;

    /**
     * Check and handle important game events. Update game state.
     */
    virtual void UpdateEvents() override ;
};

