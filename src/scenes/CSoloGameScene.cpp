/**
 * @author Jaroslav Fikar
*/


#include "CSoloGameScene.h"

void CSoloGameScene::Init()
{
    CGameScene::Init();

    this->m_Board->SetPlayers(this->m_LevelLoader.GetPlayers(1));
    this->m_LevelLoader.LoadLevel(this->m_Board, 1);

    CCoord<unsigned int> windowSize = this->m_Interface.GetWindowSize();

    // Menu texts.
    this->m_TimeText = std::make_unique<CText>(this->m_Interface,
                                               CCoord<>(10 * this->m_Board->GetCellSize(), this->m_ScenePadding), "",
                                               this->m_DefaultFontSize, SDL_Color{0, 0, 0, 255});

    // Player 1 text labels
    this->m_ScoreTexts.push_back(std::make_unique<CText>(this->m_Interface, CCoord<>(
            0.5 * this->m_Board->GetCellSize() + this->m_ScenePadding, this->m_ScenePadding), "",
                                                         this->m_DefaultFontSize));

    this->m_LivesTexts.push_back(std::make_unique<CText>(this->m_Interface, CCoord<>(
            20.5 * this->m_Board->GetCellSize() + this->m_ScenePadding, this->m_ScenePadding), "",
                                                         this->m_DefaultFontSize));

    // Scene messages locations.
    CCoord<> itemSize = this->m_GameOverText->GetSize();
    this->m_GameOverText->SetLocation(
            CCoord<>((windowSize.m_X / 2.0) - (itemSize.m_X / 2.0), (windowSize.m_Y / 2.0) - (itemSize.m_Y / 2.0)));

    itemSize = this->m_GameOverSubtext->GetSize();
    this->m_GameOverSubtext->SetLocation(
            CCoord<>((windowSize.m_X / 2.0) - (itemSize.m_X / 2.0),
                     (windowSize.m_Y / 2.0) - (itemSize.m_Y / 2.0) + this->m_DefaultFontSize * 2.5));

    // Run the game clock when the constructor is over.
    this->m_Clock = CGameClock();
}

/*====================================================================================================================*/
void CSoloGameScene::GameOver()
{
    // Save first players (the only players) score.
    if (this->m_Board->m_Players.size() == 0 || !this->m_Board->m_Players[0] ||
        !CScoreSaver(this->m_Interface.GetSettings()).TrySetTopScore(this->m_Board->m_Players[0]->GetScore()))
    {
        this->m_Interface.ShowMessageBox(SDL_MESSAGEBOX_ERROR, "Runtime error",
                                         "Cannot save new score in the file.");
        std::cerr << "Runtime error: " << "Cannot save new score in the file." << std::endl;
    }

    CGameScene::GameOver();
}

