/**
 * @author Jaroslav Fikar
 * 
*/


#include "CSettingsScene.h"

CSettingsScene::CSettingsScene(CSDLInterface &interface) : CScene(interface)
{
    this->m_Interface.SetMenuScreenSize();
    CCoord<unsigned int> windowSize = interface.GetWindowSize();
    CCoord<> itemSize;
    unsigned int padding = 10;

    SDL_Colour defaultFontColor{255, 255, 255, 255};
    SDL_Colour selectedFontColor{255, 0, 0, 255};
    SDL_Color hoverFontColor{255, 128, 0, 255};

    // Background image
    this->m_InterfaceItems.push_back(std::make_unique<CImage>(interface, CCoord<>(0, 0), windowSize.ToDouble(),
                                                              "Menu/title_background_mirror.jpg"));

    // Add select box title
    this->m_InterfaceItems.push_back(
            std::make_unique<CText>(interface, CCoord<>(0, 0), "Game screen resolution", 64));
    itemSize = this->m_InterfaceItems.back()->GetSize();
    this->m_InterfaceItems.back()->SetLocation(CCoord<>((windowSize.m_X / 2.0) - (itemSize.m_X / 2), padding));

    // Add select box
    CCoord<> selectBoxLocation = CCoord<>(0, 48);
    auto resolutions = std::map<std::string, CCoord<unsigned int>>{{"690x420",  CCoord<unsigned int>(690, 420)},
                                                                   {"1495x910", CCoord<unsigned int>(1495, 910)},
                                                                   {"1150x700", CCoord<unsigned int>(1150, 700)}};
    this->m_InterfaceItems.push_back(
            std::make_unique<CSelectBox<CCoord<unsigned int>>>(interface, selectBoxLocation,
                                                               (this->m_Interface.GetWindowSize().ToDouble() -
                                                                selectBoxLocation), 48, resolutions,
                                                               this->m_Interface.GetSettings()->GetGameScreenSize(),
                                                               defaultFontColor, hoverFontColor, selectedFontColor,
                                                               [=](CCoord<unsigned int> newRes)
                                                               { this->UpdateResolution(newRes); }));

    // Back button
    this->m_InterfaceItems.push_back(
            std::make_unique<CButton>(interface, "Back", CCoord<>(0, 0), SDL_Colour{0, 0, 0, 255}, hoverFontColor,
                                      35, [=]()
                                      { this->m_NextApplicationState = EApplicationStatus::APPLICATION_STATUS_MENU; }));
    itemSize = this->m_InterfaceItems.back()->GetSize();
    this->m_InterfaceItems.back()->SetLocation(CCoord<>(padding, windowSize.m_Y - itemSize.m_Y - padding));
}

/*====================================================================================================================*/
EApplicationStatus CSettingsScene::Run()
{
    // While window is not closed.
    while (CScene::Run() != EApplicationStatus::APPLICATION_STATUS_EXIT)
    {
        if (this->m_NextApplicationState != EApplicationStatus::APPLICATON_STATUS_NONE)
        { return this->m_NextApplicationState; }
    }

    return EApplicationStatus::APPLICATION_STATUS_MENU;
}

/*====================================================================================================================*/
void CSettingsScene::Draw() const
{
    this->m_Interface.SetRenderColor(0, 0, 0, 255);
    this->m_Interface.Clear();

    CScene::Draw();

    this->m_Interface.Present();
}

/*====================================================================================================================*/
void CSettingsScene::ProcessEvent(SDL_Event &e)
{
    switch (e.type)
    {
        case SDL_MOUSEBUTTONUP:
        case SDL_MOUSEBUTTONDOWN:
        case SDL_MOUSEMOTION:
            for (auto item = this->m_InterfaceItems.begin(); item != this->m_InterfaceItems.end(); item++)
            { item->get()->MouseEventHandler(e); }
            break;
        default:
            // Unknown events send to parent.
            CScene::ProcessEvent(e);
    }
}

