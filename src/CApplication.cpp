/**
 * @author Jaroslav Fikar
 * 
*/


#include "CApplication.h"

int CApplication::Run(int argc, char * argv[])
{
    std::shared_ptr<CSettings> settings = this->Init(argc, argv);
    std::shared_ptr<CSDLInterface> interface = std::make_shared<CSDLInterface>("Bomberman", settings);

    std::queue<CWindowManager> managers;

    try
    {
        interface->InitInterface();

        // todo add menu

        CGameManager gameManager(interface.get());

        gameManager.Run();
    }
    catch (std::ios::failure &ex)
    {
        std::cerr << ex.what() << std::endl;
        interface->ShowMessageBox(SDL_MESSAGEBOX_ERROR, MESSAGE_FILESYSTEM_ERROR, ex.what());

        return 1;
    }
    catch (std::exception &ex)
    {
        std::cerr << ex.what() << std::endl;
        interface->ShowMessageBox(SDL_MESSAGEBOX_ERROR, UNKNOWN_ERROR, ex.what());

        return 1;
    }
    catch (...)
    {
        std::cerr << UNKNOWN_ERROR << std::endl;
        interface->ShowMessageBox(SDL_MESSAGEBOX_ERROR, UNKNOWN_ERROR, UNKNOWN_ERROR);

        return 1;
    }

    return 0;
}
/*====================================================================================================================*/
std::shared_ptr<CSettings> CApplication::Init(int argc, char *argv[])
{
    // Debug mode
    bool debug = false;
    try
    {
        if (argc >= 2 && strcmp(argv[1], "-debug") == 0)
        {
            debug = true;
        }
    }
    catch(...)
    {
        std::cerr << INVALID_INPUT_PARAMETERS << std::endl;
    }


    return std::make_shared<CSettings>(1.3 * 1150, 1.3 * 700, CCoord(0, 1), 60, true, debug);
}
