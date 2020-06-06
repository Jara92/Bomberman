/**
 * @author Jaroslav Fikar
 * 
*/


#include "CMenuManager.h"

CMenuManager::CMenuManager(CSDLInterface *interface)
        : CWindowManager(interface), m_IsRunning(true)
{
    // Load textures
    this->m_Backround = this->m_Interface->LoadTexture("Menu/title_background.jpg");
    this->m_Title = this->m_Interface->LoadTexture("Menu/title_titletext.png");
    this->m_OnePlayerNormal = this->m_Interface->LoadTexture("Menu/One_Player_Normal.png");
    this->m_OnePlayerHover = this->m_Interface->LoadTexture("Menu/One_Player_Hover.png");
    this->m_TwoPlayersNormal = this->m_Interface->LoadTexture("Menu/Two_Players_Normal.png");
    this->m_TwoPlayersHover = this->m_Interface->LoadTexture("Menu/Two_Players_Hover.png");
}

/*====================================================================================================================*/
CMenuManager::~CMenuManager()
{
    // Delete textures
    SDL_DestroyTexture(this->m_Backround);
    SDL_DestroyTexture(this->m_Title);
    SDL_DestroyTexture(this->m_OnePlayerNormal);
    SDL_DestroyTexture(this->m_OnePlayerHover);
    SDL_DestroyTexture(this->m_TwoPlayersNormal);
    SDL_DestroyTexture(this->m_TwoPlayersHover);
}


/*====================================================================================================================*/
EApplicationStatus CMenuManager::Run()
{
    // While window is not closed.
    while (CWindowManager::Run() != EApplicationStatus::APPLICATION_STATUS_EXIT)
    {

    }

    return EApplicationStatus::APPLICATION_STATUS_EXIT;
}

/*====================================================================================================================*/
void CMenuManager::Update(int deltaTime)
{

}

/*====================================================================================================================*/
void CMenuManager::UpdateEvents()
{

}

/*====================================================================================================================*/
void CMenuManager::Draw() const
{
    this->m_Interface->SetRenderColor(0, 0, 0, 255);
    this->m_Interface->Clear();

    this->m_Interface->RenderTexture(this->m_Backround, CCoord(0, 0), CCoord(this->m_Interface->GetWindowSize()));

    this->m_Interface->Present();
}

