/**
 * @author Jaroslav Fikar
 * 
*/


#include "CGameManager.h"

CGameManager::CGameManager(CSDLInterface *interface)
        : CWindowManager(interface), m_Board(nullptr), m_BoardOffset(CCoord<>(0, 2)),
          m_GameStatus(EGameStatus::GAME_STATUS_RUNNING), m_NextGameStatus(EGameStatus::GAME_STATUS_RUNNING),
          m_Level(1)
{
    this->m_Interface->SetGameScreenSize();

    this->m_LevelLoader = std::make_unique<CLevelLoader>(interface);

    // Kill all players when the time runs out.
    this->m_GameEndDelay.Run(CGameManager::STARTING_TIME, [=](void)
    { this->KillAllPlayers(); });

    // Get board and load first level
    this->m_Board = this->m_LevelLoader->GetBoard(1, this->m_Interface->GetSettings());
    this->m_LevelLoader->LoadLevel(this->m_Board, 1);

    // UI items
    unsigned int padding = 5;
    this->m_DefaultFontSize = this->m_Board->GetCellSize() - 2 * padding;
    CCoord<unsigned int> windowSize = this->m_Interface->GetWindowSize();

    // Top menu background
    for (unsigned int i = 0; i < this->m_Board->GetBoardSize().m_X; i++)
    { this->m_Board->GetGroundObject()->Draw(this->m_Interface, this->m_Board->GetCellSize(), CCoord<double>(i, 0)); }

    // Menu messages
    this->m_TimeText = std::make_unique<CText>(this->m_Interface, CCoord<>(0.5 * this->m_Board->GetCellSize(), padding),
                                               "", CCoord<>(0, this->m_DefaultFontSize));

    this->m_ScoreText = std::make_unique<CText>(this->m_Interface,
                                                CCoord<>(5 * this->m_Board->GetCellSize() + padding, padding), "",
                                                CCoord<>(0, this->m_DefaultFontSize));

    this->m_LivesText = std::make_unique<CText>(this->m_Interface,
                                                CCoord<>(20.5 * this->m_Board->GetCellSize() + padding, padding), "",
                                                CCoord<>(0, this->m_DefaultFontSize));

    this->m_FPSText = std::make_unique<CText>(this->m_Interface,
                                              CCoord<>(padding, this->m_Board->GetCellSize() + padding), "",
                                              CCoord<>(0, this->m_DefaultFontSize / 2));

    // Scene messages
    this->m_RoundOverText = std::make_unique<CText>(this->m_Interface, CCoord<>(0, 0), "Round over!",
                                                    CCoord<>(0, this->m_DefaultFontSize * 3));
    CCoord<> itemSize = this->m_RoundOverText->GetSize();
    this->m_RoundOverText->SetLocation(
            CCoord<>((windowSize.m_X / 2.0) - (itemSize.m_X / 2.0), (windowSize.m_Y / 2.0) - (itemSize.m_Y / 2.0)));

    this->m_NextRoundText = std::make_unique<CText>(this->m_Interface, CCoord<>(0, 0), "Round X!",
                                                    CCoord<>(0, this->m_DefaultFontSize * 3));
    itemSize = this->m_NextRoundText->GetSize();
    this->m_NextRoundText->SetLocation(
            CCoord<>((windowSize.m_X / 2.0) - (itemSize.m_X / 2.0), (windowSize.m_Y / 2.0) - (itemSize.m_Y / 2.0)));

    this->m_GameOverText = std::make_unique<CText>(this->m_Interface, CCoord<>(0, 0), "Game over",
                                                   CCoord<>(0, this->m_DefaultFontSize * 3));
    itemSize = this->m_GameOverText->GetSize();
    this->m_GameOverText->SetLocation(
            CCoord<>((windowSize.m_X / 2.0) - (itemSize.m_X / 2.0), (windowSize.m_Y / 2.0) - (itemSize.m_Y / 2.0)));

    this->m_GameOverSubtext = std::make_unique<CText>(this->m_Interface, CCoord<>(0, 0),
                                                      "Press [ENTER] to return to the menu",
                                                      CCoord<>(0, this->m_DefaultFontSize));
    itemSize = this->m_GameOverSubtext->GetSize();
    this->m_GameOverSubtext->SetLocation(
            CCoord<>((windowSize.m_X / 2.0) - (itemSize.m_X / 2.0),
                     (windowSize.m_Y / 2.0) - (itemSize.m_Y / 2.0) + this->m_DefaultFontSize * 2.5));
}

/*====================================================================================================================*/
EApplicationStatus CGameManager::Run()
{
    while (this->m_GameStatus != EGameStatus::GAME_STATUS_EXIT)
    {
        if (CWindowManager::Run() == EApplicationStatus::APPLICATION_STATUS_EXIT)
        { return EApplicationStatus::APPLICATION_STATUS_MENU; }
    }

    return EApplicationStatus::APPLICATION_STATUS_MENU;
}

/*====================================================================================================================*/
void CGameManager::Draw() const
{
    this->m_Interface->SetRenderColor(0, 0, 0, 255);
    this->m_Interface->Clear();

    // Render screen game game status
    switch (this->m_GameStatus)
    {
        case EGameStatus::GAME_STATUS_RUNNING:
            this->DrawGame();
            break;
        case EGameStatus::GAME_STATUS_ROUND_OVER:
            this->DrawRoundOver();
            break;
        case EGameStatus::GAME_STATUS_NEXT_ROUND:
            this->DrawNextRound();
            break;
        case EGameStatus::GAMESTATUS_PAUSED:
            // TODO
            break;
        case EGameStatus::GAME_STATUS_GAME_OVER:
            this->DrawGameOver();
            break;
        default:
            break;
    }

    this->m_Interface->Present();
}

/*====================================================================================================================*/
void CGameManager::DrawGame() const
{
    this->m_Board->Draw(this->m_Interface, this->m_Interface->GetSettings()->GetOffset().ToDouble());

    // Top menu background
    for (unsigned int i = 0; i < this->m_Board->GetBoardSize().m_X; i++)
    { this->m_Board->GetGroundObject()->Draw(this->m_Interface, this->m_Board->GetCellSize(), CCoord<double>(i, 0)); }

    // Draw menu UI
    this->m_TimeText->Draw(this->m_Interface);
    this->m_ScoreText->Draw(this->m_Interface);
    this->m_LivesText->Draw(this->m_Interface);
    this->m_FPSText->Draw(this->m_Interface);
}

/*====================================================================================================================*/
void CGameManager::Update(int deltaTime)
{
    if (this->m_GameStatus == EGameStatus::GAME_STATUS_RUNNING)
    {
        this->m_Board->Update(deltaTime);
        this->m_GameEndDelay.Tick(deltaTime);

        this->m_TimeText->SetText(this->m_Interface,
                                  "Time: " + std::to_string(this->m_GameEndDelay.GetRemainingTime() / 1000),
                                  CCoord<>(0, this->m_DefaultFontSize));

        if (this->m_Board->m_Players.size() > 0 && this->m_Board->m_Players[0])
        {
            SDL_Color color = {255, 255, 255, 255};
            if (this->m_Board->m_Players[0]->GetLives() <= 0)
            { color = {128, 0, 0, 255}; }

            this->m_ScoreText->SetText(this->m_Interface,
                                       "Score: " + std::to_string(this->m_Board->m_Players[0]->GetScore()),
                                       CCoord<>(0, this->m_DefaultFontSize));

            this->m_LivesText->SetText(this->m_Interface,
                                       "Lives: " + std::to_string(std::max(0, this->m_Board->m_Players[0]->GetLives())),
                                       CCoord<>(0, this->m_DefaultFontSize), color);
        }
        this->m_FPSText->SetText(this->m_Interface, "FPS: " + std::to_string(this->m_Clock.GetFPS()),
                                 CCoord<>(0, this->m_DefaultFontSize / 2));
    }

    this->m_GameStatusDelay.Tick(deltaTime);
}

/*====================================================================================================================*/
void CGameManager::UpdateEvents()
{
    CWindowManager::UpdateEvents();

    // Read keyboard state
    const Uint8 *keystate = SDL_GetKeyboardState(NULL);

    // Catch global input keys.
    this->GlobalInput(keystate);

    // send state to all players
    for (std::vector<CPlayer *>::size_type i = 0; i < this->m_Board->m_Players.size(); i++)
    { this->m_Board->m_Players[i]->HandleInput(keystate); }

    this->m_Board->UpdatePhysicEvents();

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
        int delay = CGameManager::GAME_STATUS_UPDATE_DELAY;

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

/*====================================================================================================================*/
void CGameManager::KillAllPlayers()
{
    // Kill all players.
    for (auto player = this->m_Board->m_Players.begin(); player != this->m_Board->m_Players.end(); player++)
    {
        (*(player))->Kill();

        // Player is totally dead - game over.
        if ((*(player)) && (*(player))->GetLives() <= 0)
        { this->m_NextGameStatus = EGameStatus::GAME_STATUS_GAME_OVER; }
            // Player is not totally dead - round over.
        else if ((*(player)) && (*(player))->GetLives() > 0)
        { this->m_NextGameStatus = EGameStatus::GAME_STATUS_ROUND_OVER; }
    }
}

/*====================================================================================================================*/
void CGameManager::RoundOver()
{
    this->m_GameEndDelay.Rerun();
    this->SetStatus(EGameStatus::GAME_STATUS_RUNNING);

    // Update game state and prepare level when timer is done.
    this->m_GameStatusDelay.Run(CGameManager::GAME_STATUS_UPDATE_DELAY, [=](void)
    {
        this->m_Board->ClearBoard(false);
        this->m_LevelLoader->LoadLevel(this->m_Board, this->m_Level);
        this->UpdateStatus();
    });
}

/*====================================================================================================================*/
void CGameManager::GameOver()
{
    if (this->m_Board->m_Players.size() == 0 || !this->m_Board->m_Players[0] ||
        !CScoreSaver(this->m_Interface->GetSettings()).TrySetTopScore(this->m_Board->m_Players[0]->GetScore()))
    {
        this->m_Interface->ShowMessageBox(SDL_MESSAGEBOX_ERROR, "Runtime error",
                                          "Cannot save new score in the file.");
        std::cerr << "Runtime error: " << "Cannot save new score in the file." << std::endl;
    }

    this->m_GameEndDelay.Stop();
    this->m_GameStatusDelay.Stop();

    this->SetStatus(EGameStatus::GAME_STATUS_EXIT);
}

/*====================================================================================================================*/
void CGameManager::NextRound()
{
    this->m_Level++;
    this->m_NextRoundText->SetText(this->m_Interface, "Round " + std::to_string(this->m_Level) + "!",
                                   CCoord<>(0, this->m_DefaultFontSize * 3));

    // End game if this was last level.
    if (this->m_Level > CGameManager::GAME_LEVELS_COUNT)
    {
        this->m_NextGameStatus = EGameStatus::GAME_STATUS_GAME_OVER;
        this->GameOver();
        return;
    }

    this->m_GameEndDelay.Rerun();
    this->SetStatus(EGameStatus::GAME_STATUS_RUNNING);

    // Update game state and prepare next level when timer is done.
    this->m_GameStatusDelay.Run(CGameManager::GAME_STATUS_UPDATE_DELAY, [=](void)
    {
        this->m_Board->ClearBoard(true);
        this->m_LevelLoader->LoadLevel(this->m_Board, this->m_Level);
        this->UpdateStatus();
    });
}

/*====================================================================================================================*/
void CGameManager::GlobalInput(const Uint8 *input)
{
    // Game is over. Press enter to leave game.
    if (input[SDL_SCANCODE_RETURN]) // SDL_SCANCODE_RETURN = ENTER
    {
        if (this->m_GameStatus == EGameStatus::GAME_STATUS_GAME_OVER)
        { this->UpdateStatus(); }
    }

    // Pause game.
    if (input[SDL_SCANCODE_ESCAPE])
    {}

    // Debug options
    if (this->m_Interface->GetSettings()->GetDebugMode())
    {
        if (input[SDL_SCANCODE_F1])
        {

        } else if (input[SDL_SCANCODE_F2])
        {
            for (unsigned int i = 0; i < this->m_Board->GetBoardSize().m_X; i++)
            {
                for (unsigned int j = 0; j < this->m_Board->GetBoardSize().m_Y; j++)
                {
                    if (this->m_Board->m_Map[i][j] && this->m_Board->m_Map[i][j]->TryDestroy(0))
                    {
                        delete this->m_Board->m_Map[i][j];
                        this->m_Board->m_Map[i][j] = nullptr;
                    }
                }
            }
        } else if (input[SDL_SCANCODE_F3])
        {
            if (this->m_Board->m_Players.size() > 0 && this->m_Board->m_Players[0])
            { this->m_Board->m_Players[0]->IncreseScore(1000); }
        }
    }
}
