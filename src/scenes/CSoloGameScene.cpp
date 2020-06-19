/**
 * @author Jaroslav Fikar
 * 
*/


#include "CSoloGameScene.h"

void CSoloGameScene::Init()
{
    CGameScene::Init();

    // Get board and load first level
    this->m_Board = this->m_LevelLoader.GetBoard(1, this->m_Interface.GetSettings());
    this->m_LevelLoader.LoadLevel(this->m_Board, 1);

    unsigned int padding = 5;
    this->m_DefaultFontSize = this->m_Board->GetCellSize() - 2 * padding;
    CCoord<unsigned int> windowSize = this->m_Interface.GetWindowSize();

    // Top menu background
    for (unsigned int i = 0; i < this->m_Board->GetBoardSize().m_X; i++)
    { this->m_Board->GetGroundObject()->Draw(this->m_Interface, this->m_Board->GetCellSize(), CCoord<double>(i, 0)); }

    // Menu texts.
    this->m_TimeText = std::make_unique<CText>(this->m_Interface, CCoord<>(10 * this->m_Board->GetCellSize(), padding),
                                               "", this->m_DefaultFontSize, SDL_Color{255, 165, 0, 255});

    // Player 1 text labels
    this->m_ScoreTexts.push_back(std::make_unique<CText>(this->m_Interface,
                                                         CCoord<>(0.5 * this->m_Board->GetCellSize() + padding,
                                                                  padding),
                                                         "",
                                                         this->m_DefaultFontSize));

    this->m_LivesTexts.push_back(std::make_unique<CText>(this->m_Interface,
                                                         CCoord<>(20.5 * this->m_Board->GetCellSize() + padding,
                                                                  padding), "",
                                                         this->m_DefaultFontSize));

    this->m_FPSText = std::make_unique<CText>(this->m_Interface,
                                              CCoord<>(padding, this->m_Board->GetCellSize() + padding), "",
                                              this->m_DefaultFontSize / 2);

    // Scene messages.
    this->m_RoundOverText = std::make_unique<CText>(this->m_Interface, CCoord<>(0, 0), "Round over!",
                                                    3 * this->m_DefaultFontSize);
    CCoord<> itemSize = this->m_RoundOverText->GetSize();
    this->m_RoundOverText->SetLocation(
            CCoord<>((windowSize.m_X / 2.0) - (itemSize.m_X / 2.0), (windowSize.m_Y / 2.0) - (itemSize.m_Y / 2.0)));

    this->m_NextRoundText = std::make_unique<CText>(this->m_Interface, CCoord<>(0, 0), "Round X!",
                                                    3 * this->m_DefaultFontSize);
    itemSize = this->m_NextRoundText->GetSize();
    this->m_NextRoundText->SetLocation(
            CCoord<>((windowSize.m_X / 2.0) - (itemSize.m_X / 2.0), (windowSize.m_Y / 2.0) - (itemSize.m_Y / 2.0)));

    this->m_GameOverText = std::make_unique<CText>(this->m_Interface, CCoord<>(0, 0), "Game over",
                                                   3 * this->m_DefaultFontSize);
    itemSize = this->m_GameOverText->GetSize();
    this->m_GameOverText->SetLocation(
            CCoord<>((windowSize.m_X / 2.0) - (itemSize.m_X / 2.0), (windowSize.m_Y / 2.0) - (itemSize.m_Y / 2.0)));

    this->m_GameOverSubtext = std::make_unique<CText>(this->m_Interface, CCoord<>(0, 0),
                                                      "Press [ENTER] to return to the menu", this->m_DefaultFontSize);
    itemSize = this->m_GameOverSubtext->GetSize();
    this->m_GameOverSubtext->SetLocation(
            CCoord<>((windowSize.m_X / 2.0) - (itemSize.m_X / 2.0),
                     (windowSize.m_Y / 2.0) - (itemSize.m_Y / 2.0) + this->m_DefaultFontSize * 2.5));

    // Run the game clock when the constructor is over.
    this->m_Clock = CGameClock();
}

void CSoloGameScene::Update(int deltaTime)
{
    CGameScene::Update(deltaTime);
}

void CSoloGameScene::UpdateEvents()
{
    CGameScene::UpdateEvents();

    // If game is running.
    if (this->m_GameStatus == EGameStatus::GAME_STATUS_RUNNING && this->m_GameStatus == this->m_NextGameStatus)
    {
        // Check for dead players.
        for (auto player = this->m_Board->m_Players.begin(); player != this->m_Board->m_Players.end(); player++)
        {
            // IF player is dead.
            if ((*(player)) && !(*(player))->IsAlive())
            {
                // If player is not totally dead - Round over.
                if ((*(player))->GetLives() > 0)
                { this->m_NextGameStatus = EGameStatus::GAME_STATUS_ROUND_OVER; }
                    // Player is totally dead - Game over.
                else
                { this->m_NextGameStatus = EGameStatus::GAME_STATUS_GAME_OVER; }

                this->m_GameEndDelay.Stop();
            } else if ((*(player))->GetLevelUp())
            { this->m_NextGameStatus = EGameStatus::GAME_STATUS_NEXT_ROUND; }
        }
    }

    // Set new callback when timer is done
    if (this->m_GameStatusDelay.Done() && this->m_GameStatus != this->m_NextGameStatus)
    {
        std::function<void(void)> callBack;
        int delay = CGameScene::GAME_STATUS_UPDATE_DELAY;

        // Create callback functions for special states.
        switch (this->m_NextGameStatus)
        {
            case EGameStatus::GAME_STATUS_NEXT_ROUND:
                callBack = [=]()
                { this->NextRound(); };
                delay = 150;
                break;
            case EGameStatus::GAME_STATUS_ROUND_OVER:
                callBack = [=]()
                { this->RoundOver(); };
                break;
            case EGameStatus::GAME_STATUS_GAME_OVER:
                callBack = [=]()
                { this->GameOver(); };
                break;
            default:
                return;
        }

        // Set new callback.
        this->m_GameStatusDelay.Run(delay, callBack);
    }
}

void CSoloGameScene::GameOver()
{
    // Save first players (the only players) score.
    if (this->m_Board->m_Players.size() == 0 || !this->m_Board->m_Players[0] ||
        !CScoreSaver(this->m_Interface.GetSettings()).TrySetTopScore(this->m_Board->m_Players[0]->GetScore()))
    {
        this->m_Interface.ShowMessageBox(SDL_MESSAGEBOX_ERROR, "Runtime error",
                                         "Cannot save new score in the file.");
        std::cerr << "Runtime error: " << "Cannot save new score in the file." << std::endl;
    }

    CGameScene::GameOver();
}
