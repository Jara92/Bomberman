/**
 * @author Jaroslav Fikar
 * 
*/


#include "CMultiplayerGameScene.h"

void CMultiplayerGameScene::Init()
{
    CGameScene::Init();

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
                                               "", this->m_DefaultFontSize, SDL_Color{0, 0, 0, 255});

    // FPS
    this->m_FPSText = std::make_unique<CText>(this->m_Interface,
                                              CCoord<>(padding, this->m_Board->GetCellSize() + padding), "",
                                              this->m_DefaultFontSize / 2);

    // Player 1 text labels
    this->m_ScoreTexts.push_back(std::make_unique<CText>(this->m_Interface,
                                                         CCoord<>(3.5 * this->m_Board->GetCellSize() + padding,
                                                                  padding),
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
                                                         this->m_DefaultFontSize, SDL_Color{255, 215, 0, 255}));

    this->m_LivesTexts.push_back(std::make_unique<CText>(this->m_Interface,
                                                         CCoord<>(20.5 * this->m_Board->GetCellSize() + padding,
                                                                  padding), "",
                                                         this->m_DefaultFontSize, SDL_Color{255, 215, 0, 255}));

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

    this->m_WinnerText = std::make_unique<CText>(this->m_Interface, CCoord<>(0, 0), "PLAYER is the winner!",
                                                 this->m_DefaultFontSize * 1.3);
    itemSize = this->m_WinnerText->GetSize();
    this->m_WinnerText->SetLocation(
            CCoord<>((windowSize.m_X / 2.0) - (itemSize.m_X / 2.0),
                     (windowSize.m_Y / 2.0) - (itemSize.m_Y / 2.0) + this->m_DefaultFontSize * 2.5));

    this->m_GameOverSubtext = std::make_unique<CText>(this->m_Interface, CCoord<>(0, 0),
                                                      "Press [ENTER] to return to the menu", this->m_DefaultFontSize);
    itemSize = this->m_GameOverSubtext->GetSize();
    this->m_GameOverSubtext->SetLocation(
            CCoord<>((windowSize.m_X / 2.0) - (itemSize.m_X / 2.0),
                     (windowSize.m_Y / 2.0) - (itemSize.m_Y / 2.0) + this->m_DefaultFontSize * 5));


    // Run the game clock when the constructor is over.
    this->m_Clock = CGameClock();
}
/*====================================================================================================================*/
void CMultiplayerGameScene::Update(int deltaTime)
{
    CGameScene::Update(deltaTime);

    this->m_WinnerText->Update(this->m_Interface, deltaTime);
}
/*====================================================================================================================*/
void CMultiplayerGameScene::GameOver()
{
    // Get best player
    CPlayer *bestPlayer = nullptr;
    for (std::size_t i = 0; i < this->m_Board->m_Players.size(); i++)
    {
        if (!bestPlayer || this->m_Board->m_Players[i]->GetScore() > bestPlayer->GetScore())
        {
            bestPlayer = this->m_Board->m_Players[i];

            // Set winner text color by score.
            this->m_WinnerText->SetColor(this->m_ScoreTexts[i]->GetColor());
        }
    }

    //Save best players score.
    if (!bestPlayer || !CScoreSaver(this->m_Interface.GetSettings()).TrySetTopScore(bestPlayer->GetScore()))
    {
        this->m_Interface.ShowMessageBox(SDL_MESSAGEBOX_ERROR, "Runtime error",
                                         "Cannot save new score in the file.");
        std::cerr << "Runtime error: " << "Cannot save new score in the file." << std::endl;
    }

    // Set winner text color.
    if (this->m_Board->m_Players.size() == 2)
    {
        if (this->m_Board->m_Players[0]->GetLives() > 0 && this->m_Board->m_Players[1]->GetLives() == 0)
        { this->m_WinnerText->SetColor(this->m_ScoreTexts[0]->GetColor()); }
        else if(this->m_Board->m_Players[1]->GetLives() > 0 && this->m_Board->m_Players[0]->GetLives() == 0)
        { this->m_WinnerText->SetColor(this->m_ScoreTexts[1]->GetColor()); }
    }

    CGameScene::GameOver();
}
/*====================================================================================================================*/
void CMultiplayerGameScene::DrawGameOver() const
{
    CGameScene::DrawGameOver();
    this->m_WinnerText->Draw(this->m_Interface);
}
