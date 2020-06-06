/**
 * @author Jaroslav Fikar
 * 
*/


#include "CMenuManager.h"

CMenuManager::CMenuManager(CSDLInterface *interface)
        : CWindowManager(interface), m_IsRunning(true)
{
    this->m_Interface->SetMenuScreenSize();

    this->m_InterfaceItems.push_back(std::make_unique<CImage>(interface, CCoord(0, 0), this->m_Interface->GetWindowSize(),
                                                              "Menu/title_background.jpg"));
    this->m_InterfaceItems.push_back(std::make_unique<CImage>(interface, CCoord(0, 0), this->m_Interface->GetWindowSize(),
                                                              "Menu/title_titletext.png"));

    // Load textures
    this->m_OnePlayerNormal = this->m_Interface->LoadTexture("Menu/One_Player_Normal.png");
    this->m_OnePlayerHover = this->m_Interface->LoadTexture("Menu/One_Player_Hover.png");
    this->m_TwoPlayersNormal = this->m_Interface->LoadTexture("Menu/Two_Players_Normal.png");
    this->m_TwoPlayersHover = this->m_Interface->LoadTexture("Menu/Two_Players_Hover.png");
}

/*====================================================================================================================*/
CMenuManager::~CMenuManager()
{
    // Delete textures
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
    for(auto item = this->m_InterfaceItems.begin(); item != this->m_InterfaceItems.end(); item++)
    {
        item->get()->Update(deltaTime);
    }
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

    for(auto item = this->m_InterfaceItems.begin(); item != this->m_InterfaceItems.end(); item++)
    {
        item->get()->Draw(this->m_Interface);
    }

   // this->m_Interface->RenderTexture(this->m_Backround, CCoord(0, 0), CCoord(this->m_Interface->GetWindowSize()));
   // this->m_Interface->RenderTexture(this->m_Title, CCoord(0, 0), CCoord(this->m_Interface->GetWindowSize()));

    //  this->m_Interface->RenderTexture(this->m_Pla)

    this->m_Interface->Present();
}

