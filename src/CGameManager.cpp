/**
 * @author Jaroslav Fikar
 * 
*/


#include "CGameManager.h"

CGameManager::CGameManager(CSDLInterface *interface)
        : m_Interface(interface), m_Board(nullptr), m_GameIsRunning(true)
{
    this->m_LevelLoader = new CLevelLoader(interface);
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

        // Update objects in the board
        this->Update(this->m_Clock.DeltaTime());

        // Update physics in the board
        this->UpdatePhysics();

        // Draw board and info table
        this->Draw();

        // Wait for few miliseconds to draw cca 60 frames per second
        SDL_Delay(this->m_Clock.GetDelay());
    }
}

/*====================================================================================================================*/
void CGameManager::Draw() const
{
    this->m_Interface->SetRenderColor(0, 0, 0, 255);
    this->m_Interface->Clear();

    this->m_Board->Draw(this->m_Interface);

    // TODO Render Game menu

    // DEBUG
    this->m_Interface->RenderText(std::to_string(this->m_Clock.GetFPS()), CCoord(10, 10), CCoord(100, 50));
    //std::cout << "FPS: " << this->m_Clock.GetFPS() << std::endl;

    this->m_Interface->Present();
}

/*====================================================================================================================*/
void CGameManager::Update(int deltaTime)
{
    this->m_Board->Update(deltaTime);
}

/*====================================================================================================================*/
void CGameManager::UpdatePhysics()
{
    this->m_Board->UpdatePhysics();
}

/*====================================================================================================================*/
CGameManager::~CGameManager()
{
    delete this->m_Board;
    delete this->m_LevelLoader;
}



