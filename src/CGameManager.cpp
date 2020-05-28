/**
 * @author Jaroslav Fikar
 * 
*/


#include "CGameManager.h"

CGameManager::CGameManager(CSDLInterface *interface)
        : m_Interface(interface), m_GameIsRunning(true)
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
    //The frames per second timer
    LTimer fpsTimer;

    //The frames per second cap timer
    LTimer capTimer;

    //Start counting frames per second
    int countedFrames = 0;
    fpsTimer.start();

    while (this->m_GameIsRunning)
    {
        this->m_Clock.Tick();

        //Start cap timer
        capTimer.start();

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
//this->Update(fpsTimer.getTicks());
        // Update physics in the board
        this->UpdatePhysics();

        // Draw board and info table
        this->Draw();

        // SDL_Delay(50/3 - fpsTimer.getTicks());

        //Calculate and correct fps
        float avgFPS = countedFrames / (fpsTimer.getTicks() / 1000.f);
        if (avgFPS > 2000000)
        {
            avgFPS = 0;
        }

        std::cout << "FPS: " << avgFPS << std::endl;

        countedFrames++;

        unsigned frameTicks = capTimer.getTicks();
        if (frameTicks < this->m_Interface->GetSettings()->GetTicksPerFrame())
        {
            //Wait remaining time
            std::cout << "counted frames " << countedFrames << std::endl;
            SDL_Delay(this->m_Interface->GetSettings()->GetTicksPerFrame() - frameTicks);

        }



        // SDL_Delay(25);///3-this->m_Clock.DeltaTime());
        /*  Uint32 wait = 0;
        while(wait < 50/3)
        {
            this->m_Clock.Tick();
            wait += this->m_Clock.DeltaTime();
        }*/
        //  SDL_Delay(25); // todo edit this
        //std::cerr << this->m_Clock.DeltaTime() << std::endl;
    }
}

/*====================================================================================================================*/
void CGameManager::Draw() const
{
    this->m_Interface->SetRenderColor(0, 0, 0, 255);
    this->m_Interface->Clear();

    // TODO Render Game menu

    this->m_Board->Draw(this->m_Interface);

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



