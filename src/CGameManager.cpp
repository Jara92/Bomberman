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

void CGameManager::Init()
{
    this->m_Board = this->m_LevelLoader->GetBoard(1, this->m_Interface->GetSettings());
}

void CGameManager::Run()
{
    while(this->m_GameIsRunning){
        this->m_Clock.Tick();
        // read keyboard state
        SDL_PumpEvents();
        const Uint8 * keystate = SDL_GetKeyboardState(NULL);

        // send state to all players
        auto i = this->m_Board->m_Players.begin();
        while(i != this->m_Board->m_Players.end()){
            (*((i++).base()))->HandleInput(keystate); // TODO removed i++;
        }

        // Close window
        SDL_Event e;
        while( SDL_PollEvent( &e ) != 0 ){ // taháme události z fronty událostí
            if (e.type == SDL_QUIT) {
                this->m_GameIsRunning = false;
                return;
            }
        }

        this->Update(this->m_Clock.DeltaTime());

     //   this->UpdatePhysics();
    // this->m_Board->m_Players[0].Dra

        this->Draw();
    }
}

void CGameManager::Draw() const
{
    this->m_Interface->SetRenderColor(0,0,0,255);
    this->m_Interface->Clear();

    this->m_Board->Draw(this->m_Interface);

    this->m_Interface->Present();
}

void CGameManager::Update(int deltaTime)
{
    //this->m_Board->Update(deltaTime);
}

CGameManager::~CGameManager()
{
    delete this->m_Board;
    delete this->m_LevelLoader;
}


