/**
 * @author Jaroslav Fikar
*/

#include "CGameScene.h"

void CGameScene::Init()
{
    // Get board and load first level
    this->m_Board = this->m_LevelLoader.GetBoard(this->m_Interface.GetSettings());

    // Kill all players when the time runs out.
    this->m_GameEndTimer.Run(CGameScene::STARTING_TIME, [=](void)
    { this->KillAllPlayers(); });

    CCoord<unsigned int> windowSize = this->m_Interface.GetWindowSize();
    this->m_DefaultFontSize = this->m_Board->GetCellSize() - 2 * this->m_ScenePadding;

    // FPS text.
    this->m_FPSText = std::make_unique<CText>(this->m_Interface,
                                              CCoord<>(this->m_ScenePadding,
                                                       this->m_Board->GetCellSize() + this->m_ScenePadding), "", this->m_DefaultFontSize / 2);

    // Pause text
    this->m_PauseText = std::make_unique<CText>(this->m_Interface, CCoord<>(0, 0), "PAUSED",
                                                3 * this->m_DefaultFontSize);
    CCoord<> itemSize = this->m_PauseText->GetSize();
    this->m_PauseText->SetLocation(
            CCoord<>((this->m_Interface.GetWindowSize().m_X / 2.0) - (itemSize.m_X / 2.0),
                     (this->m_Interface.GetWindowSize().m_Y / 2.0) - (itemSize.m_Y / 2.0)));

    // Scene messages.
    this->m_RoundOverText = std::make_unique<CText>(this->m_Interface, CCoord<>(0, 0), "Round over!",
                                                    3 * this->m_DefaultFontSize);
    itemSize = this->m_RoundOverText->GetSize();
    this->m_RoundOverText->SetLocation(
            CCoord<>((windowSize.m_X / 2.0) - (itemSize.m_X / 2.0), (windowSize.m_Y / 2.0) - (itemSize.m_Y / 2.0)));

    this->m_NextRoundText = std::make_unique<CText>(this->m_Interface, CCoord<>(0, 0), "Round X!",
                                                    3 * this->m_DefaultFontSize);
    itemSize = this->m_NextRoundText->GetSize();
    this->m_NextRoundText->SetLocation(
            CCoord<>((windowSize.m_X / 2.0) - (itemSize.m_X / 2.0), (windowSize.m_Y / 2.0) - (itemSize.m_Y / 2.0)));
}

/*====================================================================================================================*/
EApplicationStatus CGameScene::Run()
{
    while (this->m_GameStatus != EGameStatus::GAME_STATUS_EXIT)
    {
        if (CScene::Run() == EApplicationStatus::APPLICATION_STATUS_EXIT)
        { return EApplicationStatus::APPLICATION_STATUS_MENU; }
    }

    return EApplicationStatus::APPLICATION_STATUS_MENU;
}

/*====================================================================================================================*/
void CGameScene::Draw() const
{
    this->m_Interface.SetRenderColor(0, 0, 0, 255);
    this->m_Interface.Clear();

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
            this->DrawPause();
            break;
        case EGameStatus::GAME_STATUS_GAME_OVER:
            this->DrawGameOver();
            break;
        default:
            break;
    }

    this->m_Interface.Present();
}

/*====================================================================================================================*/
void CGameScene::DrawGame() const
{
    this->m_Board->Draw(this->m_Interface, this->m_Interface.GetSettings().GetOffset().ToDouble());

    // Top menu background
    for (unsigned int i = 0; i < this->m_Board->GetBoardSize().m_X; i++)
    { this->m_Board->GetGroundObject()->Draw(this->m_Interface, this->m_Board->GetCellSize(), CCoord<double>(i, 0)); }

    // Draw menu UI
    this->m_TimeText->Draw(this->m_Interface);
    this->m_FPSText->Draw(this->m_Interface);

    // Draw scores and lives.
    for (std::size_t i = 0; i < this->m_ScoreTexts.size(); i++)
    {
        this->m_ScoreTexts[i]->Draw(this->m_Interface);
        this->m_LivesTexts[i]->Draw(this->m_Interface);
    }
}

/*====================================================================================================================*/
void CGameScene::DrawPause() const
{
    this->DrawGame();

    this->m_PauseText->Draw(this->m_Interface);
}

/*====================================================================================================================*/
void CGameScene::Update(int deltaTime)
{
    if (this->m_GameStatus == EGameStatus::GAME_STATUS_RUNNING)
    {
        this->m_Board->Update(deltaTime);
        this->m_GameEndTimer.Tick(deltaTime);

        this->m_TimeText->SetText("Time: " + std::to_string(this->m_GameEndTimer.GetRemainingTime() / 1000),
                                  this->m_DefaultFontSize, this->m_TimeText->GetColor());

        // Update players textboxes.
        for (std::size_t i = 0; i < this->m_Board->m_Players.size(); i++)
        {
            SDL_Color color = this->m_ScoreTexts[i]->GetColor();
            if (this->m_Board->m_Players[i]->GetLives() <= 0)
            { color = {128, 0, 0, 255}; }

            // Adding zeros.
            std::string score = std::to_string(this->m_Board->m_Players[i]->GetScore());
            std::size_t oldSize = score.size();
            if (oldSize < 10)
            {
                for (std::size_t i = 0; i < 10 - oldSize; i++)
                { score.insert(score.begin(), '0'); }
            }

            this->m_ScoreTexts[i]->SetText("Score: " + score,
                                           this->m_DefaultFontSize, this->m_ScoreTexts[i]->GetColor());
            this->m_ScoreTexts[i]->Update(this->m_Interface, deltaTime);

            this->m_LivesTexts[i]->SetText(
                    "Lives: " + std::to_string(std::max(0, this->m_Board->m_Players[i]->GetLives())),
                    this->m_DefaultFontSize, color);
            this->m_LivesTexts[i]->Update(this->m_Interface, deltaTime);
        }
        this->m_FPSText->SetText("FPS: " + std::to_string(this->m_Clock.GetFPS()), this->m_DefaultFontSize / 2,
                                 this->m_FPSText->GetColor());

        this->m_TimeText->Update(this->m_Interface, deltaTime);
        this->m_FPSText->Update(this->m_Interface, deltaTime);
    }
        // Update round over text.
    else if (this->m_GameStatus == EGameStatus::GAME_STATUS_ROUND_OVER)
    { this->m_RoundOverText->Update(this->m_Interface, deltaTime); }
        // Update next round text.
    else if (this->m_GameStatus == EGameStatus::GAME_STATUS_NEXT_ROUND)
    {
        this->m_NextRoundText->SetText("Round " + std::to_string(this->m_Level) + "!",
                                       3 * this->m_DefaultFontSize, this->m_NextRoundText->GetColor());
        this->m_NextRoundText->Update(this->m_Interface, deltaTime);
    }
        // Update game over text.
    else if (this->m_GameStatus == EGameStatus::GAME_STATUS_GAME_OVER)
    {
        this->m_GameOverText->Update(this->m_Interface, deltaTime);
        this->m_GameOverSubtext->Update(this->m_Interface, deltaTime);
    }
        // Update paused text.
    else if (this->m_GameStatus == EGameStatus::GAMESTATUS_PAUSED)
    { this->m_PauseText->Update(this->m_Interface, deltaTime); }

    this->m_GameStatusDelay.Tick(deltaTime);
}

/*====================================================================================================================*/
void CGameScene::UpdateEvents()
{
    CScene::UpdateEvents();

    // Read keyboard state
    const Uint8 *keystate = SDL_GetKeyboardState(NULL);

    // Catch global input keys.
    this->GlobalInput(keystate);

    this->m_Board->UpdatePhysicsEvents();

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

                this->m_GameEndTimer.Stop();
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

/*====================================================================================================================*/
void CGameScene::KillAllPlayers()
{
    // Kill all players.
    for (auto player = this->m_Board->m_Players.begin(); player != this->m_Board->m_Players.end(); player++)
    {
        (*(player))->TryKill();

        // Player is totally dead - game over.
        if ((*(player)) && (*(player))->GetLives() <= 0)
        {
            this->m_NextGameStatus = EGameStatus::GAME_STATUS_GAME_OVER;
            return;
        }
            // Player is not totally dead - round over.
        else if ((*(player)) && (*(player))->GetLives() > 0)
        { this->m_NextGameStatus = EGameStatus::GAME_STATUS_ROUND_OVER; }
    }
}

/*====================================================================================================================*/
void CGameScene::RoundOver()
{
    this->SetStatus(EGameStatus::GAME_STATUS_RUNNING);

    // Update game state and prepare level when timer is done.
    this->m_GameStatusDelay.Run(CGameScene::GAME_STATUS_UPDATE_DELAY, [=](void)
    {
        this->m_LevelLoader.LoadLevel(this->m_Board, this->m_Level, false);
        this->UpdateStatus();
        this->m_GameEndTimer.Reset();
    });
}

/*====================================================================================================================*/
void CGameScene::GameOver()
{
    this->m_GameEndTimer.Stop();
    this->m_GameStatusDelay.Stop();

    this->SetStatus(EGameStatus::GAME_STATUS_EXIT);
}

/*====================================================================================================================*/
void CGameScene::NextRound()
{
    this->m_Level++;

    // End game if this was last level.
    if (this->m_Level > CGameScene::GAME_LEVELS_COUNT)
    {
        this->m_NextGameStatus = EGameStatus::GAME_STATUS_GAME_OVER;
        this->GameOver();
        return;
    }

    this->SetStatus(EGameStatus::GAME_STATUS_RUNNING);

    // Update game state and prepare next level when timer is done.
    this->m_GameStatusDelay.Run(CGameScene::GAME_STATUS_UPDATE_DELAY, [=](void)
    {
        this->m_LevelLoader.LoadLevel(this->m_Board, this->m_Level, true);
        this->UpdateStatus();
        this->m_GameEndTimer.Reset();
    });
}

/*====================================================================================================================*/
void CGameScene::GlobalInput(const Uint8 *input)
{
    // Game is over. Press enter to leave game.
    if (input[SDL_SCANCODE_RETURN]) // SDL_SCANCODE_RETURN = ENTER
    {
        if (this->m_GameStatus == EGameStatus::GAME_STATUS_GAME_OVER)
        { this->UpdateStatus(); }
    }

    // Pause game.
    if (input[SDL_SCANCODE_ESCAPE] && this->m_GameStatus == this->m_NextGameStatus &&
        (this->m_GameStatus == EGameStatus::GAMESTATUS_PAUSED ||
         this->m_GameStatus == EGameStatus::GAME_STATUS_RUNNING))
    {
        if (!this->m_PauseButtonPressed)
        {
            // Pause game when the game is running.
            if (this->m_Clock.IsRunning())
            {
                this->m_Clock.Stop();
                this->m_GameStatus = this->m_NextGameStatus = EGameStatus::GAMESTATUS_PAUSED;
            } else
            {
                this->m_Clock.Reset();
                this->m_GameStatus = this->m_NextGameStatus = EGameStatus::GAME_STATUS_RUNNING;
            }

            this->m_PauseButtonPressed = true;
        }
    } else
    {
        this->m_PauseButtonPressed = false;
    }

    // Debug options
    if (this->m_Interface.GetSettings().GetDebugMode())
    {
        // Kill every enemy.
        if (input[SDL_SCANCODE_F1])
        {
            for (auto i = this->m_Board->m_Movables.begin(); i != this->m_Board->m_Movables.end(); i++)
            {
                auto *enemy = dynamic_cast<CEnemy *>(*i);

                if (enemy)
                {
                    unsigned int score = enemy->TryKill(0);
                    if (this->m_Board->m_Players.size() > 0 && this->m_Board->m_Players[0])
                    { this->m_Board->m_Players[0]->IncreseScore(score); }
                }
            }
        }
            // Destroy every destructible wall.
        else if (input[SDL_SCANCODE_F2])
        { this->m_Board->DestroyEveryDestructibleWall(); }
            // Inkrement score.
        else if (input[SDL_SCANCODE_F3])
        {
            if (this->m_Board->m_Players.size() > 0 && this->m_Board->m_Players[0])
            { this->m_Board->m_Players[0]->IncreseScore(1000); }
        }
            // Turn on rendering bounding boxes.
        else if (input[SDL_SCANCODE_F4])
        { this->m_Interface.GetSettings().SetRenderBoundingBox(true); }
    }
}

