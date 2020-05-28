/**
 * @author Jaroslav Fikar
 * 
*/


#include "CLevelLoader.h"

// Define file names
const std::string CLevelLoader::MAP_FILE_NAME = "map";
const std::string CLevelLoader::LEVEL_FILE_NAME = "level";

/*====================================================================================================================*/
bool CLevelLoader::LoadLevel(CBoard *board, size_t level)
{
    board->ClearBoard();

    // TODO přidat algoritmus na zvyšování počtu zdí podle levelu - využít board->GetBoardSize()
    size_t obstaclesCount = (board->GetBoardSize().m_X * board->GetBoardSize().m_Y) * 0.20;

    this->GenerateObstacles(board, level, obstaclesCount);

    // Load enemies and boosts
    // TODO

    return true;
}

/*====================================================================================================================*/
CBoard *CLevelLoader::GetBoard(int playersCount, CSettings *settings)
{
    // calc cellsize
    int cellSize = static_cast<int>(settings->GetScreenWidth() / CLevelLoader::MAP_WIDTH);

    // Load important objects for new board.
    std::vector<std::vector<CWall *>> map = this->LoadMap();
    std::vector<CPlayer *> players = this->LoadPlayers(playersCount);
    CGround *groundObject = this->LoadGround();
    std::shared_ptr<CTexturePack> bombTexturePack = this->LoadBombTexturePack();
    std::shared_ptr<CTexturePack> fireTexturePack = this->LoadFireTexturePack();

    return new CBoard(map, players, CCoord(CLevelLoader::MAP_WIDTH, CLevelLoader::MAP_HEIGHT), groundObject,
                      bombTexturePack, fireTexturePack,
                      cellSize);
}

/*====================================================================================================================*/
std::vector<std::vector<CWall *>> CLevelLoader::LoadMap()
{
    std::map<ETextureType, const std::vector<std::string>> textures
            {{ETextureType::TEXTURE_FRONT, std::vector<std::string>{{"Blocks/SolidBlock.png"}}}};

    std::shared_ptr<CTexturePack> texturePack =
            std::make_shared<CTexturePack>(this->m_Interface,
                                           textures);
    // create reference wall to make copies
    CWall wall(texturePack);

    // init 2D array
    std::vector<std::vector<CWall *>> map;
    map.resize(CLevelLoader::MAP_WIDTH);

    for (size_t i = 0; i < map.size(); i++)
    {
        map[i].resize(CLevelLoader::MAP_HEIGHT, nullptr);
    }

    size_t row = 0, col = 0;
    std::ifstream fileReader(this->m_Interface->GetSettings()->GetDataPath() + CLevelLoader::MAP_FILE_NAME,
                             std::ios::binary | std::ios::in);

    // Is file reader ok?
    if (!fileReader || !fileReader.is_open() || fileReader.eof() || fileReader.bad())
    {
        throw std::ios::failure(MESSAGE_MAP_ERROR);
    }

    unsigned char input = '\0';
    while ((fileReader >> std::noskipws >> input))
    {
        if (!fileReader.eof())
        {
            // Read by bite
            for (size_t i = 0; i < 8; i++)
            {
                // i-bite=1 -> Build wall on current position
                if (input >> (7 - i) & 1)
                {
                    map[static_cast<int>(col * 8 + i)][row] = new CWall(wall);
                }
            }

            // Increment col with every readed byte.
            col++;

            // Jump to next row
            if (col >= FILE_MAP_WIDTH / 8)
            {
                col = 0;
                row++;
            }

                // End if my map is full.
            else if (row >= FILE_MAP_HEIGHT)
            {
                break;
            }
        }
    }

    fileReader.close();

    return map;
}

/*========================================================================================== -==========================*/
std::vector<CPlayer *> CLevelLoader::LoadPlayers(int count)
{
    // count = 2; // todo remove
    CControls *controls[MAX_PLAYERS] = {
            new CControls(SDL_SCANCODE_W, SDL_SCANCODE_S, SDL_SCANCODE_A,
                          SDL_SCANCODE_D, SDL_SCANCODE_X, SDL_SCANCODE_C),
            new CControls(SDL_SCANCODE_I, SDL_SCANCODE_K, SDL_SCANCODE_J,
                          SDL_SCANCODE_L, SDL_SCANCODE_N, SDL_SCANCODE_M)
    };

    // Setup texturepack for the players. // TODO second player should have different texture color.
    std::map<ETextureType, const std::vector<std::string>> textures
            {{ETextureType::TEXTURE_FRONT, std::vector<std::string>{
                    {"Bomberman/Front/front0.png"},
                    {"Bomberman/Front/front1.png"},
                    {"Bomberman/Front/front2.png"},
                    {"Bomberman/Front/front3.png"},
                    {"Bomberman/Front/front4.png"},
                    {"Bomberman/Front/front5.png"},
                    {"Bomberman/Front/front6.png"},
                    {"Bomberman/Front/front7.png"}
            }},
             {ETextureType::TEXTURE_BACK,  std::vector<std::string>{
                     {"Bomberman/Back/back0.png"},
                     {"Bomberman/Back/back1.png"},
                     {"Bomberman/Back/back2.png"},
                     {"Bomberman/Back/back3.png"},
                     {"Bomberman/Back/back4.png"},
                     {"Bomberman/Back/back5.png"},
                     {"Bomberman/Back/back6.png"},
                     {"Bomberman/Back/back7.png"}
             }},
             {ETextureType::TEXTURE_LEFT,  std::vector<std::string>{
                     {"Bomberman/Left/left0.png"},
                     {"Bomberman/Left/left1.png"},
                     {"Bomberman/Left/left2.png"},
                     {"Bomberman/Left/left3.png"},
                     {"Bomberman/Left/left4.png"},
                     {"Bomberman/Left/left5.png"},
                     {"Bomberman/Left/left6.png"},
                     {"Bomberman/Left/left7.png"}
             }},
             {ETextureType::TEXTURE_RIGHT, std::vector<std::string>{
                     {"Bomberman/Right/right0.png"},
                     {"Bomberman/Right/right1.png"},
                     {"Bomberman/Right/right2.png"},
                     {"Bomberman/Right/right3.png"},
                     {"Bomberman/Right/right4.png"},
                     {"Bomberman/Right/right5.png"},
                     {"Bomberman/Right/right6.png"},
                     {"Bomberman/Right/right7.png"}
             }}};

    std::vector<std::map<ETextureType, const std::vector<std::string>>> texturePacks{{textures},
                                                                                     {textures}};

    // Setup default locations
    CCoord startingLocation[CLevelLoader::MAX_PLAYERS] = {{1,  1},
                                                          {21, 11}};

    std::vector<CPlayer *> players;

    // return only required players
    for (int i = 0; i < count; i++)
    {
        players.push_back(
                new CPlayer(std::make_shared<CTexturePack>(this->m_Interface, texturePacks[i], false, CCoord(1, 2)),
                            startingLocation[i],
                            controls[i]));
        controls[i] = nullptr;
    }

    // delete unused objects
    for (size_t i = 0; i < CLevelLoader::MAX_PLAYERS; i++)
    {
        delete controls[i];
    }

    return players;
}

/*====================================================================================================================*/
void CLevelLoader::GenerateObstacles(CBoard *board, size_t level, size_t count)
{
    std::map<ETextureType, const std::vector<std::string>> textures
            {{ETextureType::TEXTURE_FRONT, std::vector<std::string>{{"Blocks/ExplodableBlock.png"}}}};

    std::shared_ptr<CTexturePack> texturePack =
            std::make_shared<CTexturePack>(this->m_Interface,
                                           textures);
    size_t randomX = 0, randomY = 0;

    for (size_t i = 0; i < count; i++)
    {
        // Generate random location until the location is free.
        do
        {
            randomX = rand() % static_cast<int>(board->GetBoardSize().m_X);
            randomY = rand() % static_cast<int>(board->GetBoardSize().m_Y);
        } while (!board->PositionFree(CCoord(randomX, randomY)));

        board->m_Map[randomX][randomY] = new CWall(texturePack, CCoord(randomX, randomY), true, nullptr);

    }

}

/*====================================================================================================================*/
CGround *CLevelLoader::LoadGround()
{
    std::map<ETextureType, const std::vector<std::string>> textures
            {{ETextureType::TEXTURE_FRONT, std::vector<std::string>{{"Blocks/BackgroundTile.png"}}}};

    std::shared_ptr<CTexturePack> texturePack =
            std::make_shared<CTexturePack>(this->m_Interface,
                                           textures);
    // create reference wall to make copies
    return new CGround(texturePack);
}

/*====================================================================================================================*/
std::shared_ptr<CTexturePack> CLevelLoader::LoadBombTexturePack()
{
    // TODO Use other bomb textures - change texture with bomb life
    std::map<ETextureType, const std::vector<std::string>> textures
            {{ETextureType::TEXTURE_FRONT, std::vector<std::string>{{"Bomb/Bomb_f01.png"}}}};

    return std::make_shared<CTexturePack>(this->m_Interface,
                                          textures, true, CCoord(0.65, 0.65));
}

/*====================================================================================================================*/
std::shared_ptr<CTexturePack> CLevelLoader::LoadFireTexturePack()
{
    std::map<ETextureType, const std::vector<std::string>> textures
            {{ETextureType::TEXTURE_FRONT, std::vector<std::string>{{"Flame/Flame_f00.png"},
                                                                    {"Flame/Flame_f01.png"},
                                                                    {"Flame/Flame_f02.png"},
                                                                    {"Flame/Flame_f03.png"},
                                                                    {"Flame/Flame_f04.png"}}}};

    return std::make_shared<CTexturePack>(this->m_Interface,
                                          textures, true, CCoord(0.65, 0.65));
}


