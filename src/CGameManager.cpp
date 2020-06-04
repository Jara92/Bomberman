/**
 * @author Jaroslav Fikar
 * 
*/


#include "CGameManager.h"

// Define file names
const std::string CLevelLoader::MAP_FILE_NAME = "map";
const std::string CLevelLoader::LEVEL_FILE_NAME = "level";

CGameManager::CGameManager(CSDLInterface *interface)
        : m_Interface(interface), m_Board(nullptr), m_BoardOffset(CCoord(0, 2)), m_GameIsRunning(true),
          m_GameStatus(EGameStatus::GAMESTATUS_RUNNING),
          m_Level(1), m_RemainingTime(CGameManager::STARTING_TIME),
          m_NextGameStatus(EGameStatus::GAMESTATUS_RUNNING)
{
    this->m_LevelLoader = new CLevelLoader(interface);
    this->m_GameEndDelay.Run(this->GAME_STATUS_DELAY);
}

/*====================================================================================================================*/
void CGameManager::Init()
{
    this->m_Board = this->m_LevelLoader->GetBoard(1, this->m_Interface->GetSettings());

    this->m_LevelLoader->LoadLevel(this->m_Board, 1);
}

/*====================================================================================================================*/
void CGameManager::Run()
{
    while (this->m_GameIsRunning)
    {
        this->m_Clock.Tick();

        // read keyboard state
        SDL_PumpEvents();
        const Uint8 *keystate = SDL_GetKeyboardState(NULL);

        // send state to all players
        for (std::vector<CPlayer *>::size_type i = 0; i < this->m_Board->m_Players.size(); i++)
        {
            this->m_Board->m_Players[i]->HandleInput(keystate);
        }

        // Check events
        SDL_Event e;
        while (SDL_PollEvent(&e) != 0)
        {
            // Close window
            if (e.type == SDL_QUIT)
            {
                this->m_GameIsRunning = false;
                return;
            }
        }

        // Check physics events physics in the board
        this->UpdateGameStatus();

        // Update objects in the board
        this->Update(this->m_Clock.DeltaTime());

        // Draw game
        this->Draw();

        // Wait for few miliseconds to draw cca 60 frames per second
        this->m_Interface->Wait(this->m_Clock.GetDelay());
    }
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
    this->m_Board->Draw(this->m_Interface, this->m_Interface->GetSettings()->GetOffset());

    // Top menu background
    for (unsigned int i = 0; i < this->m_Board->GetBoardSize().m_X; i++)
    {
        this->m_Board->GetGroundObject()->Draw(this->m_Interface, this->m_Board->GetCellSize(), CCoord(i, 0));
    }

    // Menu
    this->m_Interface->RenderText("Score: " + std::to_string(this->m_Board->m_Players[0]->GetScore()),
                                  CCoord(10, 10),
                                  CCoord(0, this->m_Board->GetCellSize() - 20));

    this->m_Interface->RenderText("Time: " + std::to_string(this->m_GameEndDelay.GetRemainingTime() / 1000),
                                  CCoord(10 * this->m_Board->GetCellSize() + 10, 10),
                                  CCoord(0, this->m_Board->GetCellSize() - 20));

    if (this->m_Board->m_Players.size() > 0 && this->m_Board->m_Players[0])
    {
        this->m_Interface->RenderText("Lives: " + std::to_string(std::max(0, this->m_Board->m_Players[0]->GetLives())),
                                      CCoord(20 * this->m_Board->GetCellSize() + 10, 10),
                                      CCoord(2 * this->m_Board->GetCellSize(), this->m_Board->GetCellSize() - 20));
    }

    // Fps counter
    this->m_Interface->RenderText("FPS: " + std::to_string(this->m_Clock.GetFPS()),
                                  CCoord(10, this->m_Board->GetCellSize() + 10), CCoord(50, 25));
}

/*====================================================================================================================*/
void CGameManager::DrawRoundOver() const
{
    CCoord textSize = CCoord(400, 100);
    this->m_Interface->RenderText("Round over!",
                                  CCoord((this->m_Interface->GetSettings()->GetScreenWidth() / 2) - textSize.m_X / 2,
                                         (this->m_Interface->GetSettings()->GetScreenHeight() / 2) - textSize.m_Y / 2),
                                  textSize);
}

/*====================================================================================================================*/
void CGameManager::DrawNextRound() const
{
    CCoord textSize = CCoord(400, 100);
    this->m_Interface->RenderText("Round " + std::to_string(this->m_Level) + "!",
                                  CCoord((this->m_Interface->GetSettings()->GetScreenWidth() / 2) - textSize.m_X / 2,
                                         (this->m_Interface->GetSettings()->GetScreenHeight() / 2) - textSize.m_Y / 2),
                                  textSize);
}

/*====================================================================================================================*/
void CGameManager::DrawGameOver() const
{
    CCoord textSize = CCoord(400, 100);
    this->m_Interface->RenderText("Game over",
                                  CCoord((this->m_Interface->GetSettings()->GetScreenWidth() / 2) - textSize.m_X / 2,
                                         (this->m_Interface->GetSettings()->GetScreenHeight() / 2) - textSize.m_Y / 2),
                                  textSize);
    // TODO write score
}


/*====================================================================================================================*/
void CGameManager::Update(int deltaTime)
{
    if (this->m_GameStatus == EGameStatus::GAMESTATUS_RUNNING)
    {
        this->m_Board->Update(deltaTime);
        this->m_GameEndDelay.Tick(deltaTime);
    }

    this->m_GameStatusDelay.Tick(deltaTime);
}

/*====================================================================================================================*/
void CGameManager::UpdateGameStatus()
{
    this->m_Board->UpdatePhysics();

    if (this->m_GameStatus == EGameStatus::GAMESTATUS_RUNNING)
    {
        for (auto player = this->m_Board->m_Players.begin(); player != this->m_Board->m_Players.end(); player++)
        {
            if (!(*(player.base()))->IsAlive())
            {
                if (!this->m_GameStatusDelay.IsRunning())
                {
                    this->m_GameStatusDelay.Run(3000);
                }

                if ((*(player.base()))->GetLives() >= 0)
                {
                    this->m_NextGameStatus = EGameStatus::GAMESTATUS_ROUND_OVER;
                } else
                {
                    this->m_NextGameStatus = EGameStatus::GAME_STATUS_GAME_OVER;
                }
            }
        }

        if (this->m_GameEndDelay.Done())
        {
            this->m_GameEndDelay.Stop();
            for (auto player = this->m_Board->m_Players.begin(); player != this->m_Board->m_Players.end(); player++)
            {
                (*(player.base()))->Kill();
                this->m_NextGameStatus = this->m_Board->RoundOver((*(player.base())));

                if (this->m_NextGameStatus != this->m_GameStatus && !this->m_GameStatusDelay.IsRunning())
                {
                    this->m_GameStatusDelay.Run(3000);
                }

                if (this->m_NextGameStatus == EGameStatus::GAME_STATUS_GAME_OVER)
                {
                    break;
                }
            }
        }
    }

    // Updating game using new gamestatus
    switch (this->m_GameStatus)
    {
        case EGameStatus::GAMESTATUS_NEXT_ROUND:
            this->m_Level++;
            this->m_LevelLoader->LoadLevel(this->m_Board, this->m_Level);

            this->m_NextGameStatus = EGameStatus::GAMESTATUS_RUNNING;
            this->m_GameStatusDelay.Run(3000);
            break;
        case EGameStatus::GAMESTATUS_ROUND_OVER:
            this->m_Board->ClearBoard();
            this->m_LevelLoader->LoadLevel(this->m_Board, this->m_Level);

            if (!this->m_GameStatusDelay.IsRunning())
            {
                this->m_NextGameStatus = EGameStatus::GAMESTATUS_RUNNING;
                this->m_GameStatusDelay.Run(3000);
            }

            break;
        case EGameStatus::GAME_STATUS_GAME_OVER:

            break;
        default:
            break;
    }

    if (this->m_GameStatusDelay.Done())
    {
        this->m_GameStatusDelay.Stop();
        this->m_GameStatus = this->m_NextGameStatus;

        this->m_Clock.Reset();

        this->m_GameEndDelay.Rerun();

    }
}

void CGameManager::LevelOver()
{

}

/*====================================================================================================================*/
CGameManager::~CGameManager()
{
    delete this->m_Board;
    delete this->m_LevelLoader;
}






