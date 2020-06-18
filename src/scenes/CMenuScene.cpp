/**
 * @author Jaroslav Fikar
*/

#include "CMenuScene.h"

/**
 * Menu window.
 * @param interface Interface to be used.
 */
CMenuScene::CMenuScene(CSDLInterface &interface)
        : CScene(interface)
{
    // Set menu window size.
    this->m_Interface.SetMenuScreenSize();
    CCoord<unsigned int> windowSize = this->m_Interface.GetWindowSize();
    CCoord<> itemSize;

    unsigned int offset = 10, yLocation = offset, fontSize = 64, yButtonMargin = 70;

    SDL_Colour textColor = {255, 255, 255, 255}, textHoverColor = {255, 128, 0, 255};

    // Background image
    this->m_InterfaceItems.push_back(std::make_unique<CImage>(interface, CCoord<>(0, 0), windowSize.ToDouble(),
                                                              "Menu/title_background.jpg"));
    // Title text
    this->m_InterfaceItems.push_back(
            std::make_unique<CText>(interface, CCoord<>(0, 0), "Bomberman!", 2 * fontSize));
    itemSize = this->m_InterfaceItems.back()->GetSize();
    this->m_InterfaceItems.back()->SetLocation(CCoord<>((windowSize.m_X / 2.0) - (itemSize.m_X / 2), yLocation));

    // Top score
    this->m_InterfaceItems.push_back(
            std::make_unique<CText>(interface, CCoord<>(0, 0),
                                    "Highest score: " +
                                    std::to_string(CScoreSaver(this->m_Interface.GetSettings()).GetTopScore()),
                                    fontSize / 1.5, SDL_Color{255, 215, 0, 255}));
    itemSize = this->m_InterfaceItems.back()->GetSize();
    this->m_InterfaceItems.back()->SetLocation(
            CCoord<>(windowSize.m_X / 2.0 - itemSize.m_X / 2, yLocation += static_cast<unsigned int>(1.8 * fontSize)));

    // One player button
    this->m_InterfaceItems.push_back(
            std::make_unique<CButton>(interface, "One player", CCoord<>(0, 0), textColor, textHoverColor, fontSize,
                                      [=]()
                                      { this->m_NextApplicationState = EApplicationStatus::APPLICATION_STATUS_SOLO_GAME; }));

    itemSize = this->m_InterfaceItems.back()->GetSize();
    this->m_InterfaceItems.back()->SetLocation(
            CCoord<>((windowSize.m_X / 2.0) - (itemSize.m_X / 2),
                     yLocation += static_cast<unsigned int>(yButtonMargin * 0.75)));

    // Two players button
    this->m_InterfaceItems.push_back(
            std::make_unique<CButton>(interface, "Two players", CCoord<>(0, 0), textColor, textHoverColor, fontSize,
                                      [=]()
                                      { this->m_NextApplicationState = EApplicationStatus::APPLICATION_STATUS_MULTI_GAME; }));

    itemSize = this->m_InterfaceItems.back()->GetSize();
    this->m_InterfaceItems.back()->SetLocation(
            CCoord<>((windowSize.m_X / 2.0) - (itemSize.m_X / 2), yLocation += yButtonMargin));

    // Settings button
    this->m_InterfaceItems.push_back(
            std::make_unique<CButton>(interface, "Settings", CCoord<>(0, 0), textColor, textHoverColor,fontSize, [=]()
                                      { this->m_NextApplicationState = EApplicationStatus::APPLICATION_STATUS_SETTINGS; }));

    itemSize = this->m_InterfaceItems.back()->GetSize();
    this->m_InterfaceItems.back()->SetLocation(
            CCoord<>((windowSize.m_X / 2.0) - (itemSize.m_X / 2), yLocation += yButtonMargin));

    // Exit button
    this->m_InterfaceItems.push_back(
            std::make_unique<CButton>(interface, "Exit", CCoord<>(0, 0), textColor, textHoverColor,fontSize, [=]()
                                      { this->m_NextApplicationState = EApplicationStatus::APPLICATION_STATUS_EXIT; }));

    itemSize = this->m_InterfaceItems.back()->GetSize();
    this->m_InterfaceItems.back()->SetLocation(
            CCoord<>((windowSize.m_X / 2.0) - (itemSize.m_X / 2), yLocation += yButtonMargin));

    // Footer
    this->m_InterfaceItems.push_back(
            std::make_unique<CText>(interface, CCoord<>(0, 0), "Jaroslav Fikar 2020", fontSize / 2.0,SDL_Color{0, 0, 0, 255}));

    // Move footer in right-bottom corner
    itemSize = this->m_InterfaceItems.back()->GetSize();
    this->m_InterfaceItems.back()->SetLocation(
            CCoord<>(windowSize.m_X - itemSize.m_X - offset, windowSize.m_Y - itemSize.m_Y - offset));
}

/*====================================================================================================================*/
EApplicationStatus CMenuScene::Run()
{
    // While window is not closed.
    while (CScene::Run() != EApplicationStatus::APPLICATION_STATUS_EXIT)
    {
        if (this->m_NextApplicationState != EApplicationStatus::APPLICATON_STATUS_NONE)
        { return this->m_NextApplicationState; }
    }

    return EApplicationStatus::APPLICATION_STATUS_EXIT;
}

/*====================================================================================================================*/
void CMenuScene::Draw() const
{
    this->m_Interface.SetRenderColor(0, 0, 0, 255);
    this->m_Interface.Clear();

    CScene::Draw();

    this->m_Interface.Present();
}

/*====================================================================================================================*/
void CMenuScene::ProcessEvent(SDL_Event &e)
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

