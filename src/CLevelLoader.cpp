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
    return false;
}

/*====================================================================================================================*/
CBoard *CLevelLoader::GetBoard(int playersCount, CSettings *settings)
{
    // calc cellsize
    int cellSize = static_cast<int>(settings->GetScreenWidth() / CLevelLoader::MAP_WIDTH);

    CGameObject ***map = this->LoadMap();
    std::vector<CPlayer *> players = this->LoadPlayers(playersCount);

    return new CBoard(map, players, CCoord(CLevelLoader::MAP_WIDTH, CLevelLoader::MAP_HEIGHT), cellSize);
}

/*====================================================================================================================*/
CGameObject ***CLevelLoader::LoadMap()
{
    // create reference wall to make copies
  /*  std::map<unsigned int, const std::string > mapa {{0, "ahoj"}};
    std::shared_ptr<CTexturePack> texturePack =
            std::make_shared<CTexturePack>(this->m_Interface,
                    std::map<ETextureType, std::map<unsigned int, const std::string>>{{mapa}});*/

    CWall wall(texturePack);




    // init 2D array
    CGameObject ***map = new CGameObject **[MAP_WIDTH];
    for (size_t i = 0; i < CLevelLoader::MAP_WIDTH; i++)
    {
        map[i] = new CGameObject *[CLevelLoader::MAP_HEIGHT];

        for (size_t j = 0; j < CLevelLoader::MAP_HEIGHT; j++)
        {
            map[i][j] = nullptr;
        }
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
            if (col >= MAP_WIDTH / 8)
            {
                col = 0;
                row++;
            }

                // End if my map is full.
            else if (row >= MAP_HEIGHT)
            {
                break;
            }
        }
    }

    fileReader.close();

    return map;
}

/*====================================================================================================================*/
std::vector<CPlayer *> CLevelLoader::LoadPlayers(int count)
{
    count = 2;
    CControls *controls[MAX_PLAYERS] = {
            new CControls(SDL_SCANCODE_W, SDL_SCANCODE_S, SDL_SCANCODE_A,
                          SDL_SCANCODE_D, SDL_SCANCODE_X, SDL_SCANCODE_C),
            new CControls(SDL_SCANCODE_I, SDL_SCANCODE_K, SDL_SCANCODE_J,
                          SDL_SCANCODE_L, SDL_SCANCODE_N, SDL_SCANCODE_M)
    };

    std::vector<std::map<ETextureType, const std::string>> texturePacks{
            std::map<ETextureType, const std::string>{{ETextureType::TEXTURE_STATIC, "Bomberman/Front/front0.png"},
                                                      {ETextureType::TEXTURE_UP,     "Bomberman/Back/back0.png"},
                                                      {ETextureType::TEXTURE_DOWN,   "Bomberman/Front/front0.png"},
                                                      {ETextureType::TEXTURE_LEFT,   "Bomberman/Left/left0.png"},
                                                      {ETextureType::TEXTURE_RIGHT,  "Bomberman/Right/right0.png"}},

            std::map<ETextureType, const std::string>{{ETextureType::TEXTURE_STATIC, "Bomberman/Front/front0.png"},
                                                      {ETextureType::TEXTURE_UP,     "Bomberman/Back/back0.png"},
                                                      {ETextureType::TEXTURE_DOWN,   "Bomberman/Front/front0.png"},
                                                      {ETextureType::TEXTURE_LEFT,   "Bomberman/Left/left0.png"},
                                                      {ETextureType::TEXTURE_RIGHT,  "Bomberman/Right/right0.png"}}
    };

    CCoord startingLocation[CLevelLoader::MAX_PLAYERS] = {{1,  1},
                                                          {21, 11}};

    std::vector<CPlayer *> players;

    // return only required players
    for (int i = 0; i < count; i++)
    {
        players.push_back(
                new CPlayer(std::make_shared<CTexturePack>(this->m_Interface, texturePacks[i], CCoord(1, 2)),
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

    //return std::vector<CPlayer*>();
}


