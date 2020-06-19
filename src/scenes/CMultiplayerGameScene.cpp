/**
 * @author Jaroslav Fikar
 * 
*/


#include "CMultiplayerGameScene.h"

void CMultiplayerGameScene::Init()
{

    std::cout << "mul" << std::endl;
    // Kill all players when the time runs out.
    this->m_GameEndDelay.Run(CGameScene::/*GAME_STATUS_UPDATE_DELAY*/STARTING_TIME, [=](void)
    { this->KillAllPlayers(); });

    // Get board and load first level
    this->m_Board = this->m_LevelLoader.GetBoard(2, this->m_Interface.GetSettings());
    this->m_LevelLoader.LoadLevel(this->m_Board, 1);

    unsigned int padding = 5;
    this->m_DefaultFontSize = this->m_Board->GetCellSize() - 2 * padding;
    CCoord<unsigned int> windowSize = this->m_Interface.GetWindowSize();

    // Top menu background
    for (unsigned int i = 0; i < this->m_Board->GetBoardSize().m_X; i++)
    { this->m_Board->GetGroundObject()->Draw(this->m_Interface, this->m_Board->GetCellSize(), CCoord<double>(i, 0)); }

    // Menu texts.
    this->m_TimeText = std::make_unique<CText>(this->m_Interface, CCoord<>(10 * this->m_Board->GetCellSize(), padding),
                                               "", this->m_DefaultFontSize, SDL_Color{0,0,0,255});

    // FPS
    this->m_FPSText = std::make_unique<CText>(this->m_Interface,
                                              CCoord<>(padding, this->m_Board->GetCellSize() + padding), "",
                                              this->m_DefaultFontSize / 2);

    // Player 1 text labels
    this->m_ScoreTexts.push_back(std::make_unique<CText>(this->m_Interface,
                                                         CCoord<>(3.5 * this->m_Board->GetCellSize() + padding, padding),
                                                         "",
                                                         this->m_DefaultFontSize));

    this->m_LivesTexts.push_back(std::make_unique<CText>(this->m_Interface,
                                                         CCoord<>(0.5 * this->m_Board->GetCellSize() + padding,
                                                                  padding), "",
                                                         this->m_DefaultFontSize));
    // Player 2 text labels
    this->m_ScoreTexts.push_back(std::make_unique<CText>(this->m_Interface,
                                                         CCoord<>(14 * this->m_Board->GetCellSize() + padding, padding),
                                                         "",
                                                         this->m_DefaultFontSize, SDL_Color{255,215,0,255}));

    this->m_LivesTexts.push_back(std::make_unique<CText>(this->m_Interface,
                                                         CCoord<>(20.5 * this->m_Board->GetCellSize() + padding,
                                                                  padding), "",
                                                         this->m_DefaultFontSize, SDL_Color{255,215,0,255}));

    // Scene messages.
    this->m_RoundOverText = std::make_unique<CText>(this->m_Interface, CCoord<>(0, 0), "Round over!",
                                                    3 * this->m_DefaultFontSize);
    CCoord<> itemSize = this->m_RoundOverText->GetSize();
    this->m_RoundOverText->SetLocation(
            CCoord<>((windowSize.m_X / 2.0) - (itemSize.m_X / 2.0), (windowSize.m_Y / 2.0) - (itemSize.m_Y / 2.0)));

    this->m_NextRoundText = std::make_unique<CText>(this->m_Interface, CCoord<>(0, 0), "Round X!",
                                                    3 * this->m_DefaultFontSize);
    itemSize = this->m_NextRoundText->GetSize();
    this->m_NextRoundText->SetLocation(
            CCoord<>((windowSize.m_X / 2.0) - (itemSize.m_X / 2.0), (windowSize.m_Y / 2.0) - (itemSize.m_Y / 2.0)));

    this->m_GameOverText = std::make_unique<CText>(this->m_Interface, CCoord<>(0, 0), "Game over",
                                                   3 * this->m_DefaultFontSize);
    itemSize = this->m_GameOverText->GetSize();
    this->m_GameOverText->SetLocation(
            CCoord<>((windowSize.m_X / 2.0) - (itemSize.m_X / 2.0), (windowSize.m_Y / 2.0) - (itemSize.m_Y / 2.0)));

    this->m_GameOverSubtext = std::make_unique<CText>(this->m_Interface, CCoord<>(0, 0),
                                                      "Press [ENTER] to return to the menu", this->m_DefaultFontSize);
    itemSize = this->m_GameOverSubtext->GetSize();
    this->m_GameOverSubtext->SetLocation(
            CCoord<>((windowSize.m_X / 2.0) - (itemSize.m_X / 2.0),
                     (windowSize.m_Y / 2.0) - (itemSize.m_Y / 2.0) + this->m_DefaultFontSize * 2.5));

    // Run the game clock when the constructor is over.
    this->m_Clock = CGameClock();
}

void CMultiplayerGameScene::Update(int deltaTime)
{
    CGameScene::Update(deltaTime);
}

void CMultiplayerGameScene::UpdateEvents()
{
    CGameScene::UpdateEvents();
}
