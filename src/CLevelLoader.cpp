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

CBoard *CLevelLoader::GetBoard(int players, CSettings *settings)
{
    // calc cellsize
    int cellSize = static_cast<int>(settings->GetScreenWidth() / CLevelLoader::MAP_WIDTH);

    CGameObject ***map = this->LoadMap();

    return new CBoard(map, CCoord(CLevelLoader::MAP_WIDTH, CLevelLoader::MAP_HEIGHT), cellSize);
}

CGameObject ***CLevelLoader::LoadMap()
{
    // create reference wall to make copies
    std::shared_ptr<CTexturePack> texturePack = std::make_shared<CTexturePack>(this->m_Interface,
                                                                               std::map<ETextureType,
                                                                                       const std::string>{{ETextureType::TEXTURE_STATIC, "Blocks/SolidBlock.png"}});
    CWall wall(texturePack);

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
    std::ifstream fileReader(this->m_Interface->GetSettings()->GetDataPath() + CLevelLoader::MAP_FILE_NAME, std::ios::binary | std::ios::in);

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
                    std::cout << "*";
                }
                else std::cout << "o";
            }

            // Increment col with every readed byte.
            col++;

            // Jump to next row
            if (col >= MAP_WIDTH / 8)
            {
                col = 0;
                std::cout << std::endl;
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


