/**
 * @author Jaroslav Fikar
 * 
*/


#include "CLevelLoader.h"

// Define map file name
const std::string CLevelLoader::MAP_FILE_NAME = "map";

bool CLevelLoader::LoadLevel(CBoard &board, size_t level)
{
    return false;
}

CBoard *CLevelLoader::GetBoard(int playersCount, CSettings *settings)
{
    // calc cellsize
    int cellSize = static_cast<int>(settings->GetScreenWidth() / CLevelLoader::MAP_WIDTH);

    CGameObject ***map = this->LoadMap();
    std::vector<CPlayer *> players = this->LoadPlayers(playersCount);

    return new CBoard(map, players, CCoord(CLevelLoader::MAP_WIDTH, CLevelLoader::MAP_HEIGHT), cellSize);
}

CGameObject ***CLevelLoader::LoadMap()
{
    // create reference wall to make copies
    std::shared_ptr<CTexturePack> texturePack = std::make_shared<CTexturePack>(this->m_Interface,
                                                                               std::map<ETextureType,
                                                                                       const std::string>{{ETextureType::TEXTURE_STATIC, "Blocks/SolidBlock.png"}});
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
                    map[static_cast<int>(col * 8 + i)][row] = wall.Clone();
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
            std::map<ETextureType, const std::string>{{ETextureType::TEXTURE_STATIC, "Bomberman/Front/Bman_F_f00.png"},
                                                      {ETextureType::TEXTURE_UP,     "Bomberman/Back/Bman_B_f00.png"},
                                                      {ETextureType::TEXTURE_DOWN,   "Bomberman/Front/Bman_F_f00.png"},
                                                      {ETextureType::TEXTURE_LEFT,   "Bomberman/Left/Bman_F_f00.png"},
                                                      {ETextureType::TEXTURE_RIGHT,  "Bomberman/Right/Bman_F_f00.png"}},

            std::map<ETextureType, const std::string>{{ETextureType::TEXTURE_STATIC, "Bomberman/Front/Bman_F_f00.png"},
                                                      {ETextureType::TEXTURE_UP,     "Bomberman/Back/Bman_B_f00.png"},
                                                      {ETextureType::TEXTURE_DOWN,   "Bomberman/Front/Bman_F_f00.png"},
                                                      {ETextureType::TEXTURE_LEFT,   "Bomberman/Left/Bman_F_f00.png"},
                                                      {ETextureType::TEXTURE_RIGHT,  "Bomberman/Right/Bman_F_f00.png"}}
    };

    CCoord startingLocation[CLevelLoader::MAX_PLAYERS] = {{0, 0},
                                                          {0, 7}};

    std::vector<CPlayer *> players;

    // return only required players
    for (int i = 0; i < count; i++)
    {
        players.push_back(
                new CPlayer(std::make_shared<CTexturePack>(this->m_Interface, texturePacks[i]), startingLocation[i],
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


