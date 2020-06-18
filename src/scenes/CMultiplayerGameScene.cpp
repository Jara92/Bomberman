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
    this->m_TimeText = std::make_unique<CText>(this->m_Interface, CCoord<>(0.5 * this->m_Board->GetCellSize(), padding),
                                               "", this->m_DefaultFontSize);

    // FPS
    this->m_FPSText = std::make_unique<CText>(this->m_Interface,
                                              CCoord<>(padding, this->m_Board->GetCellSize() + padding), "",
                                              this->m_DefaultFontSize / 2);
}

void CMultiplayerGameScene::Update(int deltaTime)
{
    // Add rendering Sologame scene. // fixme
    if (this->m_GameStatus == EGameStatus::GAME_STATUS_RUNNING)
    {
        this->m_Board->Update(deltaTime);
        this->m_GameEndDelay.Tick(deltaTime);
    }

    this->m_GameStatusDelay.Tick(deltaTime);
}

void CMultiplayerGameScene::UpdateEvents()
{
    CGameScene::UpdateEvents();
}
