/**
 * @author Jaroslav Fikar
 * 
*/


#include "CSettingsManager.h"

CSettingsManager::CSettingsManager(CSDLInterface *interface) : CWindowManager(interface)
{
    this->m_Interface->SetMenuScreenSize();
    CCoord windowSize = interface->GetWindowSize();
    CCoord itemSize;
    unsigned int padding = 10;

    // Add select box title
    this->m_InterfaceItems.push_back(
            std::make_unique<CText>(interface, CCoord(0, 0), "Game screen resolution", CCoord(0, 64)));
    itemSize = this->m_InterfaceItems.back()->GetSize();
    this->m_InterfaceItems.back()->SetLocation(
            CCoord((windowSize.m_X / 2) - (itemSize.m_X / 2), padding));

    // Add select box
    CCoord selectBoxLocation = CCoord(0, 48);
    this->m_InterfaceItems.push_back(
            std::make_unique<CSelectBox>(interface, selectBoxLocation,
                                         this->m_Interface->GetWindowSize() - selectBoxLocation, 48,
                                         std::vector<std::string>{{"1200x500"},
                                                                  {"500x200"}}, SDL_Colour{255, 255, 255, 255},
                                         SDL_Color{255, 128, 0, 255}, SDL_Colour{255, 0, 0, 255}));
    // TODO add sound
}

/*====================================================================================================================*/
EApplicationStatus CSettingsManager::Run()
{
    // While window is not closed.
    while (CWindowManager::Run() != EApplicationStatus::APPLICATION_STATUS_EXIT)
    {
        if (this->m_NextApplicationState != EApplicationStatus::APPLICATON_STATUS_NONE)
        { return this->m_NextApplicationState; }
    }

    return EApplicationStatus::APPLICATION_STATUS_EXIT;
}

/*====================================================================================================================*/
void CSettingsManager::Update(int deltaTime)
{

}

/*====================================================================================================================*/
void CSettingsManager::UpdateEvents()
{
    CWindowManager::UpdateEvents();
}

/*====================================================================================================================*/
void CSettingsManager::Draw() const
{
    this->m_Interface->SetRenderColor(0, 0, 0, 255);
    this->m_Interface->Clear();

    CWindowManager::Draw();

    this->m_Interface->Present();
}

/*====================================================================================================================*/
void CSettingsManager::ProcessEvent(SDL_Event &e)
{
    switch (e.type)
    {
        case SDL_MOUSEBUTTONUP:
        case SDL_MOUSEBUTTONDOWN:
        case SDL_MOUSEMOTION:
            for (auto item = this->m_InterfaceItems.begin(); item != this->m_InterfaceItems.end(); item++)
            {
                item->get()->MouseEventHandler(e);
            }
            break;
        default:
            // Unknown events send to parent.
            CWindowManager::ProcessEvent(e);
    }
}

