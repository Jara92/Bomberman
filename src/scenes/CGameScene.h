/**
 * @author Jaroslav Fikar
*/

#pragma once

#include <functional>
#include "CScene.h"
#include "../CSDLInterface.h"
#include "../CGameClock.h"
#include "../CBoard.h"
#include "../CLevelLoader.h"
#include "../enums/EGameStatus.h"
#include "../CTimer.h"
#include "../CScoreSaver.h"

/** Manager for single player game. */
class CGameScene : public CScene
{
public:
    /**
     * Constructor.
     * @param interface Interface to be used.
     */
    explicit CGameScene(CSDLInterface &interface);

    virtual ~CGameScene() = default;

    CGameScene(const CGameScene &other) = delete;

    CGameScene &operator=(const CGameScene &other) = delete;

    /**
     * Run the game.
     * @returns Next application status.
    */
    virtual EApplicationStatus Run() override;

    virtual void Init() override
    {}

protected:
    std::shared_ptr<CBoard> m_Board;
    /** The board must be drawn shifted because of top menu. */
    CCoord<> m_BoardOffset;
    CLevelLoader m_LevelLoader;
    /** Current game state. */
    EGameStatus m_GameStatus;
    /** next game state which will be set when m_GameStatusDelay is done. */
    EGameStatus m_NextGameStatus;
    unsigned int m_Level;
    /** Timer which detects expiration of time. */
    CTimer m_GameEndDelay;
    /** Timer which updates game state updates a time delay. */
    CTimer m_GameStatusDelay;

    /** UI items which has special meaning. */
    std::unique_ptr<CText> m_TimeText, m_ScoreText, m_LivesText, m_FPSText;
    std::unique_ptr<CText> m_RoundOverText, m_NextRoundText, m_GameOverText, m_GameOverSubtext;
    unsigned int m_DefaultFontSize;

    /** The time a player has to complete the game.*/
    static constexpr int STARTING_TIME = 200500;
    /** Waiting time between loading scenes. */
    static constexpr int GAME_STATUS_UPDATE_DELAY = 2000;
    /** Number of game levels. (Last level id is equal to GAME_LEVELS_COUNT )*/
    static constexpr int GAME_LEVELS_COUNT = 10;

    /**
     * Global input events.
     * @param input Keystate
     */
    void GlobalInput(const Uint8 *input);

    /** Prepare board for next round. */
    void NextRound();

    /** Reload current level. */
    void RoundOver();

    /** Save top score and shut off the game. */
    void GameOver();

    /**
     * Fill game state with value of next game state and fill next game state with value of newStatus.
     * @param newStatus New game state.
     */
    void SetStatus(EGameStatus newStatus)
    {
        this->m_GameStatus = this->m_NextGameStatus;
        this->m_NextGameStatus = newStatus;
    }

    /** Fill game state with value of next game state. */
    void UpdateStatus()
    { this->m_GameStatus = this->m_NextGameStatus; }

    void KillAllPlayers();

    /** Draw game by the game state. */
    virtual void Draw() const override;

    void DrawGame() const;

    void DrawRoundOver() const
    { this->m_RoundOverText->Draw(this->m_Interface); }

    void DrawNextRound() const
    { this->m_NextRoundText->Draw(this->m_Interface); }

    void DrawGameOver() const
    {
        this->m_GameOverText->Draw(this->m_Interface);
        this->m_GameOverSubtext->Draw(this->m_Interface);
    }

    /**
     * Update game.
     * @param deltaTime Delta time.
     */
    virtual void Update(int deltaTime) override;

    /** Check and handle important game events. Update game state. */
    virtual void UpdateEvents() override;
};

