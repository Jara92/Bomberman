/**
 * @author Jaroslav Fikar
 * 
*/


#include "CMenuManager.h"

CMenuManager::CMenuManager(CSDLInterface *interface)
        : CWindowManager(interface), m_IsRunning(true),
          m_NextApplicationState(EApplicationStatus::APPLICATON_STATUS_NONE)
{
    this->m_Interface->SetMenuScreenSize();
    CCoord windowSize = this->m_Interface->GetWindowSize();
    CCoord itemSize;
    unsigned int offset = 10;
    unsigned int yLocation = offset;
    unsigned int basicFontSize = 64;
    unsigned int yButtonMargin = 80;

    // Background image
    this->m_InterfaceItems.push_back(std::make_unique<CImage>(interface, CCoord(0, 0), windowSize,
                                                              "Menu/title_background.jpg"));
    // Title text
    this->m_InterfaceItems.push_back(std::make_unique<CText>(interface, CCoord(0, 0), "Bomberman!", CCoord(0, 2 * basicFontSize)));
    itemSize = this->m_InterfaceItems.back()->GetSize();
    this->m_InterfaceItems.back()->SetLocation(
            CCoord((windowSize.m_X / 2) - (itemSize.m_X / 2), yLocation));

    // One player button
    this->m_InterfaceItems.push_back(
            std::make_unique<CButton>(std::make_unique<CText>(interface, CCoord(0, 0), "One player", CCoord(0, basicFontSize)),
                                      [=]()
                                      { this->m_NextApplicationState = EApplicationStatus::APPLICATION_STATUS_SOLO_GAME; },
                                      std::make_unique<CText>(interface, CCoord(0, 0), "One player", CCoord(0, basicFontSize), SDL_Color{255,128,0,255})));
    itemSize = this->m_InterfaceItems.back()->GetSize();
    this->m_InterfaceItems.back()->SetLocation(
            CCoord((windowSize.m_X / 2) - (itemSize.m_X / 2), yLocation += yButtonMargin * 1.5));

    // Two players button
    this->m_InterfaceItems.push_back(
            std::make_unique<CButton>(std::make_unique<CText>(interface, CCoord(0, 0), "Two players", CCoord(0, basicFontSize)),
                                      [=]()
                                      { this->m_NextApplicationState = EApplicationStatus::APPLICATION_STATUS_SOLO_GAME; },
                                      std::make_unique<CText>(interface, CCoord(0, 0), "Two players", CCoord(0, basicFontSize), SDL_Color{255,128,0,255})));
    itemSize = this->m_InterfaceItems.back()->GetSize();
    this->m_InterfaceItems.back()->SetLocation(
            CCoord((windowSize.m_X / 2) - (itemSize.m_X / 2), yLocation += yButtonMargin));

    // Settings button
    this->m_InterfaceItems.push_back(
            std::make_unique<CButton>(std::make_unique<CText>(interface, CCoord(0, 0), "Settings", CCoord(0, basicFontSize)),
                                      [=]()
                                      { this->m_NextApplicationState = EApplicationStatus::APPLICATION_STATUS_SOLO_GAME; },
                                      std::make_unique<CText>(interface, CCoord(0, 0), "Settings", CCoord(0, basicFontSize), SDL_Color{255,128,0,255})));
    itemSize = this->m_InterfaceItems.back()->GetSize();
    this->m_InterfaceItems.back()->SetLocation(
            CCoord((windowSize.m_X / 2) - (itemSize.m_X / 2), yLocation += yButtonMargin));

    // Exit button
    this->m_InterfaceItems.push_back(
            std::make_unique<CButton>(std::make_unique<CText>(interface, CCoord(0, 0), "Exit", CCoord(0, basicFontSize)),
                                      [=]()
                                      { this->m_NextApplicationState = EApplicationStatus::APPLICATION_STATUS_SOLO_GAME; },
                                      std::make_unique<CText>(interface, CCoord(0, 0), "Exit", CCoord(0, basicFontSize), SDL_Color{255,128,0,255})));
    itemSize = this->m_InterfaceItems.back()->GetSize();
    this->m_InterfaceItems.back()->SetLocation(
            CCoord((windowSize.m_X / 2) - (itemSize.m_X / 2), yLocation += yButtonMargin));

    // Footer
    this->m_InterfaceItems.push_back(
            std::make_unique<CText>(interface, CCoord(0, 0), "Jaroslav Fikar 2020", CCoord(0, basicFontSize / 2.0),
                                    SDL_Color{0, 0, 0, 255}));
    // Move footer in right-bottom corner
    itemSize = this->m_InterfaceItems.back()->GetSize();
    this->m_InterfaceItems.back()->SetLocation(
            CCoord(windowSize.m_X - itemSize.m_X - offset, windowSize.m_Y - itemSize.m_Y - offset));

}

/*====================================================================================================================*/
CMenuManager::~CMenuManager()
{
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
    for (auto item = this->m_InterfaceItems.begin(); item != this->m_InterfaceItems.end(); item++)
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

    for (auto item = this->m_InterfaceItems.begin(); item != this->m_InterfaceItems.end(); item++)
    {
        item->get()->Draw(this->m_Interface);
    }

    // this->m_Interface->RenderTexture(this->m_Backround, CCoord(0, 0), CCoord(this->m_Interface->GetWindowSize()));
    // this->m_Interface->RenderTexture(this->m_Title, CCoord(0, 0), CCoord(this->m_Interface->GetWindowSize()));

    //  this->m_Interface->RenderTexture(this->m_Pla)

    this->m_Interface->Present();
}

