/**
 * @author Jaroslav Fikar
 * 
*/


#include "CLevelLoader.h"

CLevelLoader::CLevelLoader(CSDLInterface *interface)
        : m_Interface(interface)
{
    this->m_EnemyTexturePacks = this->LoadEnemyTexturePacks();
    this->m_CollectibleTexturePacks = this->LoadCollectiblesTexturePacks();
}

/*====================================================================================================================*/
CCoord CLevelLoader::RandomBoardLocation(std::shared_ptr<CBoard> &board)
{
    // Random number generator.
    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    std::default_random_engine randomEngine(seed);

    // Return random location on the board.
    return CCoord(static_cast<double>(randomEngine() % static_cast<int>(board->GetBoardSize().m_X)),
                  static_cast<double>(randomEngine() % static_cast<int>(board->GetBoardSize().m_Y)));
}

/*====================================================================================================================*/
bool CLevelLoader::LoadLevel(std::shared_ptr<CBoard> &board, size_t level)
{
    // Generate random obstacles.
    size_t obstaclesCount = (board->GetBoardSize().m_X * board->GetBoardSize().m_Y) * 0.15;
    this->GenerateObstacles(board, level, obstaclesCount);

    // Load enemies and boosts from the file.
    this->LoadLevelFile(board, level, board->m_Collectibles.empty());

    // Random location for every collectable object.
    this->ReorganizeCollectibles(board);

    return true;
}

/*====================================================================================================================*/
std::shared_ptr<CBoard> CLevelLoader::GetBoard(int playersCount, CSettings *settings)
{
    // calc cellsize
    int cellSize = static_cast<int>((settings->GetScreenHeight()) /
                                    (CLevelLoader::MAP_HEIGHT + settings->GetOffset().m_Y));

    // Load important objects for new board.
    std::shared_ptr<CTexturePack> bombTexturePack = this->LoadBombTexturePack();
    std::shared_ptr<CTexturePack> fireTexturePack = this->LoadFireTexturePack();
    std::vector<std::vector<CWall *>> map = this->LoadMap();
    std::vector<CPlayer *> players = this->LoadPlayers(playersCount);
    std::shared_ptr<CGround> groundObject = this->LoadGround();

    return std::make_shared<CBoard>(settings, map, players, CCoord(CLevelLoader::MAP_WIDTH, CLevelLoader::MAP_HEIGHT),
                                    groundObject,
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
        throw std::ios::failure(MESSAGE_MAP_NOT_FOUND);
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
                          SDL_SCANCODE_D, SDL_SCANCODE_SPACE, SDL_SCANCODE_C),
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
                            startingLocation[i], CCoord(0.5, 0.75),
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
void CLevelLoader::GenerateObstacles(std::shared_ptr<CBoard> &board, size_t level, size_t count)
{
    std::map<ETextureType, const std::vector<std::string>> textures
            {{ETextureType::TEXTURE_FRONT, std::vector<std::string>{{"Blocks/ExplodableBlock.png"}}}};

    std::shared_ptr<CTexturePack> texturePack = std::make_shared<CTexturePack>(this->m_Interface, textures);

    for (size_t i = 0; i < count; i++)
    {
        // Generate random location until the location is free.
        CCoord random;
        do
        {
            random = this->RandomBoardLocation(board);
        } while (!board->PositionFree(random) || !board->PlayersAreaFree(random));

        board->m_Map[static_cast<int>(random.m_X)][static_cast<int>(random.m_Y)] = new CWall(texturePack, CCoord(1, 1),
                                                                                             CCoord(static_cast<int>(random.m_X),
                                                                                                    static_cast<int>(random.m_Y)),
                                                                                             true, nullptr);
    }
}

/*====================================================================================================================*/
std::shared_ptr<CGround> CLevelLoader::LoadGround()
{
    std::map<ETextureType, const std::vector<std::string>> textures
            {{ETextureType::TEXTURE_FRONT, std::vector<std::string>{{"Blocks/BackgroundTile.png"}}}};

    std::shared_ptr<CTexturePack> texturePack =
            std::make_shared<CTexturePack>(this->m_Interface,
                                           textures);
    // create reference wall to make copies
    return std::make_shared<CGround>(CGround(texturePack));
}

/*====================================================================================================================*/
std::shared_ptr<CTexturePack> CLevelLoader::LoadBombTexturePack()
{
    std::map<ETextureType, const std::vector<std::string>> textures
            {{ETextureType::TEXTURE_FRONT, std::vector<std::string>{{"Bomb/Bomb_f01.png"},
                                                                    {"Bomb/Bomb_f02.png"},
                                                                    {"Bomb/Bomb_f03.png"}}}};

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

/*====================================================================================================================*/
std::vector<std::shared_ptr<CTexturePack>> CLevelLoader::LoadEnemyTexturePacks()
{
    std::vector<std::shared_ptr<CTexturePack>> textures;

    return textures;
}

/*====================================================================================================================*/
std::vector<std::shared_ptr<CTexturePack>> CLevelLoader::LoadCollectiblesTexturePacks()
{
    // Save textures in right order - ECollectibleType texturePack = textures[(int)ECollectibleType)]
    std::vector<std::map<ETextureType, const std::vector<std::string>>> textures
            {
                    {{ETextureType::TEXTURE_FRONT, std::vector<std::string>{{"Powerups/SpeedPowerup.png"}}}},
                    {{ETextureType::TEXTURE_FRONT, std::vector<std::string>{{"Powerups/FlamePowerup.png"}}}},
                    {{ETextureType::TEXTURE_FRONT, std::vector<std::string>{{"Powerups/SpeedPowerup.png"}}}},
                    {{ETextureType::TEXTURE_FRONT, std::vector<std::string>{{"Powerups/SpeedPowerup.png"}}}},
                    {{ETextureType::TEXTURE_FRONT, std::vector<std::string>{{"Powerups/SpeedPowerup.png"}}}},
                    {{ETextureType::TEXTURE_FRONT, std::vector<std::string>{{"Powerups/SpeedPowerup.png"}}}},
                    {{ETextureType::TEXTURE_FRONT, std::vector<std::string>{{"Powerups/SpeedPowerup.png"}}}},
                    {{ETextureType::TEXTURE_FRONT, std::vector<std::string>{{"Powerups/SpeedPowerup.png"}}}},
                    {{ETextureType::TEXTURE_FRONT, std::vector<std::string>{{"Blocks/Portal.png"}}}}};

    // Create texture packs shared pointers.
    std::vector<std::shared_ptr<CTexturePack>> texturePacks;
    for (size_t i = 0; i < textures.size(); i++)
    {
        texturePacks.push_back(std::make_shared<CTexturePack>(this->m_Interface, textures[i], true));
    }

    return texturePacks;
}

/*====================================================================================================================*/
void CLevelLoader::LoadLevelFile(std::shared_ptr<CBoard> &board, unsigned int level, bool loadCollectibles)
{
    std::ifstream fileReader(
            (this->m_Interface->GetSettings()->GetDataPath() + CLevelLoader::LEVEL_FILE_NAME) + std::to_string(level),
            std::ios::in);

    // Is file reader ok?
    if (!fileReader || !fileReader.is_open() || fileReader.eof() || fileReader.bad())
    {
        throw std::ios::failure(MESSAGE_LEVEL_NOT_FOUND);
    }

    // Read all lines and crate object for every line
    std::string line;
    while (std::getline(fileReader, line))
    {
        // Split string
        std::istringstream iss(line);
        std::vector<std::string> results(std::istream_iterator<std::string>{iss},
                                         std::istream_iterator<std::string>());
        // Skip empty lines
        if (results.empty())
        { break; }

        // Read item type and
        std::string itemType = this->ReadProperty(results, 0);

        // Do not load collectibles when loadCollectibles = false.
        if (loadCollectibles || itemType != "collectible")
        { this->ReadItem(board, results, itemType); }

        // TODO DUBUG
        /*  for (std::vector<std::string>::size_type i = 0; i < results.size(); i++)
          { std::cout << results[i] << "x"; }*/
        //std::cout << std::endl;
    }

    fileReader.close();
}

/*====================================================================================================================*/
std::string
CLevelLoader::ReadProperty(const std::vector<std::string> &input, std::vector<std::string>::size_type index) const
{
    if (index >= input.size())
    {
        throw std::out_of_range(MESSAGE_INDEX_OUT_OF_BOUND);
    }

    return input[index];
}

/*====================================================================================================================*/
void CLevelLoader::ReorganizeCollectibles(std::shared_ptr<CBoard> &board)
{
    std::map<CCoord, CCollectible * > collectibles;
    for(auto collectible = board->m_Collectibles.begin(); collectible != board->m_Collectibles.end(); collectible++)
    {
        // Generate random location until the CWall at this location is null or indestructible or already has collectable object.
        CCoord random;
        do
        {
            random = this->RandomBoardLocation(board);
        } while (!board->m_Map[random.GetFlooredX()][random.GetFlooredY()] ||
                 !board->m_Map[random.GetFlooredX()][random.GetFlooredY()]->IsDestructible() ||
                 board->m_Map[random.GetFlooredX()][random.GetFlooredY()]->HasCollectible());

        // Insert collectible with new location to new map and attach it to the wall.
        if (collectible->second && board->m_Map[random.GetFlooredX()][random.GetFlooredY()])
        {
            collectible->second->SetLocation(random);
            board->m_Map[random.GetFlooredX()][random.GetFlooredY()]->AttachCollectible(collectible->second);
            collectibles.insert(std::pair<CCoord, CCollectible *>(random, collectible->second));
        }
    }

    board->m_Collectibles = collectibles;
}

/*====================================================================================================================*/
bool CLevelLoader::CreateCollectibleAtRandomLocation(std::shared_ptr<CBoard> &board, ECollectibleType type,
                                                     std::size_t score, std::size_t duration)
{
    // Generate totaly random inicialization location.
    CCoord random = this->RandomBoardLocation(board);

    // Lamda which are used to apply / deactivate collectable item.
    std::function<void(CPlayer *)> applyFunc;
    std::function<void(CPlayer *)> deactivateFunc;

    // Create new boost.
    switch (type)
    {
        case ECollectibleType::COLLECTIBLE_TYPE_SPEED:
            applyFunc = [](CPlayer *player)
            { player->SpeedUp(); };
            board->m_Collectibles.insert(std::pair<CCoord, CCollectible *>(random, (new CBoost(
                    this->m_CollectibleTexturePacks[static_cast<int>(type)], applyFunc, CCoord(1, 1), random,
                    score))));
            break;
        case ECollectibleType::COLLECTIBLE_TYPE_DOOR:
            board->m_Collectibles.insert(std::pair<CCoord, CCollectible *>(random, (new CDoor(
                    this->m_CollectibleTexturePacks[static_cast<int>(type)], CCoord(1, 1), random, score))));
            break;
        default:
            throw std::invalid_argument(UNKNOWN_COLLECTIBLE_TYPE);
            break;
    }

    return true;
}

/*====================================================================================================================*/
bool CLevelLoader::ReadItem(std::shared_ptr<CBoard> &board, const std::vector<std::string> &input,
                            const std::string &itemType)
{
    try
    {
        // Collectible item
        if (itemType == "collectible" && input.size() == COLLECTIBLE_ITEM_PROPERTIES_COUNT)
        {
            // Load other properties.
            int collectibleTypeId = std::stoi(this->ReadProperty(input, 1));
            std::size_t score = std::stoi(this->ReadProperty(input, 2));
            std::size_t duration = std::stoi(this->ReadProperty(input, 3));

            // Invalid collectible type id detection.
            if (collectibleTypeId >= this->m_CollectibleTexturePacks.size())
            {
                throw std::invalid_argument(UNKNOWN_COLLECTIBLE_TYPE + std::to_string(collectibleTypeId) + " " +
                                            std::to_string(this->m_CollectibleTexturePacks.size()));
            }

            ECollectibleType collectibleType = static_cast<ECollectibleType >(collectibleTypeId);

            this->CreateCollectibleAtRandomLocation(board, collectibleType, score, duration);
        }
            // Enemy+ std::to_string(" ")
        else if (itemType == "enemy" && input.size() == ENEMY_ITEM_PROPERTIES_COUNT)
        {

        }
            // Unknown type
        else
        {
            std::cerr << INVALID_ITEM << itemType << " Input size: " << input.size() << std::endl;
            for (std::vector<std::string>::size_type i = 0; i < input.size(); i++)
            { std::cerr << input[i] << " "; }
            std::cerr << std::endl;
            return false;
        }
    }
    catch (std::invalid_argument &ex)
    {
        std::cerr << INVALID_ARGUMENT << " " << ex.what() << std::endl;
        return false;
    }
    catch (std::out_of_range &ex)
    {
        std::cerr << INT_OVERFLOW << std::endl;
        return false;
    }

    return true;
}









