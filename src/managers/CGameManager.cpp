/**
 * @author Jaroslav Fikar
 * 
*/


#include "CGameManager.h"

CGameManager::CGameManager(CSDLInterface *interface)
        : CWindowManager(interface), m_Board(nullptr), m_BoardOffset(CCoord<>(0, 2)),
          m_GameStatus(EGameStatus::GAMESTATUS_RUNNING), m_NextGameStatus(EGameStatus::GAMESTATUS_RUNNING),
          m_Level(1)
{
    this->m_Interface->SetGameScreenSize();

    this->m_LevelLoader = std::make_unique<CLevelLoader>(interface);

    // Kill all players when the time runs out.
    this->m_GameEndDelay.Run(this->STARTING_TIME, [=](void)
    { this->KillAllPlayers(); });

    // Get board and load first level
    this->m_Board = this->m_LevelLoader->GetBoard(1, this->m_Interface->GetSettings());
    this->m_LevelLoader->LoadLevel(this->m_Board, 1);

    // UI items
    unsigned int padding = 5;
    this->m_DefaultFontSize = this->m_Board->GetCellSize() - 2 * padding;

    // Top menu background
    for (unsigned int i = 0; i < this->m_Board->GetBoardSize().m_X; i++)
    { this->m_Board->GetGroundObject()->Draw(this->m_Interface, this->m_Board->GetCellSize(), CCoord<double>(i, 0)); }

    // Menu
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
        case EGameStatus::GAMESTATUS_RUNNING:
            this->DrawGame();
            break;
        case EGameStatus::GAMESTATUS_ROUND_OVER:
            this->DrawRoundOver();
            break;
        case EGameStatus::GAMESTATUS_NEXT_ROUND:
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
void CGameManager::DrawRoundOver() const
{
    CCoord<> textSize = CCoord<>(400, 100);
    this->m_Interface->RenderText("Round over!", CCoord<>(
            (this->m_Interface->GetSettings()->GetGameScreenSize().m_X / 2) - textSize.m_X / 2,
            (this->m_Interface->GetSettings()->GetGameScreenSize().m_Y / 2) - textSize.m_Y / 2), textSize);
}

/*====================================================================================================================*/
void CGameManager::DrawNextRound() const
{
    CCoord<> textSize = CCoord<>(400, 100);
    this->m_Interface->RenderText("Round " + std::to_string(this->m_Level) + "!", CCoord<>(
            (this->m_Interface->GetSettings()->GetGameScreenSize().m_X / 2) - textSize.m_X / 2,
            (this->m_Interface->GetSettings()->GetGameScreenSize().m_Y / 2) - textSize.m_Y / 2), textSize);
}

/*====================================================================================================================*/
void CGameManager::DrawGameOver() const
{
    CCoord<unsigned int> screenSize = CCoord<unsigned int>(
            this->m_Interface->GetSettings()->GetGameScreenSize().m_X,
            this->m_Interface->GetSettings()->GetGameScreenSize().m_Y);
    CCoord<double> textSize = CCoord<double>(screenSize.m_X / 4.0, screenSize.m_X / 14.0);
    this->m_Interface->RenderText("Game over", CCoord<double>(screenSize.m_X / 2.0 - (textSize.m_X / 2.0),
                                                              (screenSize.m_Y / 2.0) - (textSize.m_Y / 2)),
                                  textSize);

    textSize = CCoord<double>(screenSize.m_X / 3.0, screenSize.m_X / 30.0);
    this->m_Interface->RenderText("Press [ENTER] to return to the menu",
                                  CCoord<double>((screenSize.m_X / 2.0) - (textSize.m_X / 2.0),
                                                 (screenSize.m_Y / 2.0 + textSize.m_Y +
                                                  2 * this->m_Board->GetCellSize()) - textSize.m_Y / 2.0),
                                  textSize);
}

/*====================================================================================================================*/
void CGameManager::Update(int deltaTime)
{
    if (this->m_GameStatus == EGameStatus::GAMESTATUS_RUNNING)
    {
        this->m_Board->Update(deltaTime);
        this->m_GameEndDelay.Tick(deltaTime);

        this->m_TimeText->SetText(this->m_Interface,
                                  "Time: " + std::to_string(this->m_GameEndDelay.GetRemainingTime() / 1000),
                                  CCoord<>(0, this->m_DefaultFontSize));

        if (this->m_Board->m_Players.size() > 0 && this->m_Board->m_Players[0])
        {

            SDL_Color color = {255, 255, 255, 255};
            if (this->m_Board->m_Players[0]->GetLives() < 0)
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

    this->m_Board->UpdatePhysics();

    // If game is running.
    if (this->m_GameStatus == EGameStatus::GAMESTATUS_RUNNING && this->m_GameStatus == this->m_NextGameStatus)
    {
        // Check for dead players.
        for (auto player = this->m_Board->m_Players.begin(); player != this->m_Board->m_Players.end(); player++)
        {
            // IF player is dead.
            if ((*(player.base())) && !(*(player.base()))->IsAlive())
            {
                // If player is not totally dead - Round over.
                if ((*(player.base()))->GetLives() >= 0)
                { this->m_NextGameStatus = EGameStatus::GAMESTATUS_ROUND_OVER; }
                    // Player is totally dead - Game over.
                else
                { this->m_NextGameStatus = EGameStatus::GAME_STATUS_GAME_OVER; }

                this->m_GameEndDelay.Stop();
            } else if ((*(player.base()))->GetLevelUp())
            { this->m_NextGameStatus = EGameStatus::GAMESTATUS_NEXT_ROUND; }
        }
    }

    // Set new callback when timer is done
    if (this->m_GameStatusDelay.Done() && this->m_GameStatus != this->m_NextGameStatus)
    {
        std::function<void(void)> callBack;
        int delay = CGameManager::GAME_STATUS_DELAY;

        // Create callback functions for special states.
        switch (this->m_NextGameStatus)
        {
            case EGameStatus::GAMESTATUS_NEXT_ROUND:
                callBack = [=]()
                { this->NextRound(); };
                delay = 150;
                break;
            case EGameStatus::GAMESTATUS_ROUND_OVER:
                callBack = [=]()
                { this->RoundOver(); };
                break;
            case EGameStatus::GAME_STATUS_GAME_OVER:
                callBack = [=]()
                { this->GameOver(); };
                break;
            default:
                callBack = [=]()
                {};
                break;
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
        (*(player.base()))->Kill();

        // Player is totally dead - game over.
        if ((*(player.base())) && (*(player.base()))->GetLives() < 0)
        { this->m_NextGameStatus = EGameStatus::GAME_STATUS_GAME_OVER; }
            // Player is not totally dead - round over.
        else if ((*(player.base())) && (*(player.base()))->GetLives() >= 0)
        { this->m_NextGameStatus = EGameStatus::GAMESTATUS_ROUND_OVER; }
    }
}

/*====================================================================================================================*/
void CGameManager::RoundOver()
{
    // Clear board, load level and refresh game end delay.
    this->m_Board->ClearBoard(false);
    this->m_LevelLoader->LoadLevel(this->m_Board, this->m_Level);
    this->m_GameEndDelay.Rerun();

    this->SetStatus(EGameStatus::GAMESTATUS_RUNNING);

    // Update game state when timer is done.
    this->m_GameStatusDelay.Run(CGameManager::GAME_STATUS_DELAY, [=](void)
    { this->UpdateStatus(); });
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

    this->SetStatus(EGameStatus::GAME_STATUS_EXIT);
}

/*====================================================================================================================*/
void CGameManager::NextRound()
{
    this->m_Board->ClearBoard();

    // Level up, load new level from the file and refresh game end delay.
    this->m_Level++;
    this->m_LevelLoader->LoadLevel(this->m_Board, this->m_Level);
    this->m_GameEndDelay.Rerun();

    this->SetStatus(EGameStatus::GAMESTATUS_RUNNING);

    this->m_GameStatusDelay.Run(CGameManager::GAME_STATUS_DELAY, [=](void)
    { this->UpdateStatus(); });
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












