/**
 * @author Jaroslav Fikar
 * 
*/


#include "CApplication.h"

int CApplication::Run(int argc, char *argv[])
{
    std::shared_ptr<CSettings> settings = this->Init(argc, argv);
    std::shared_ptr<CSDLInterface> interface = std::make_shared<CSDLInterface>("Bomberman", settings,
                                                                               "Fonts/Piedra-Regular.ttf");
    try
    {
        interface->InitInterface();
        EApplicationStatus applicationStatus = EApplicationStatus::APPLICATION_STATUS_MENU;

        while (applicationStatus != EApplicationStatus::APPLICATION_STATUS_EXIT)
        {
            // Get manager to be run.
            std::shared_ptr<CWindowManager> manager = this->GetWindowManagerByState(interface.get(),
                                                                                    applicationStatus);

            // Run and get next application state.
            applicationStatus = manager->Run();
        }
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
std::shared_ptr <CSettings> CApplication::Init(int argc, char *argv[])
{
    // Debug mode
    bool debug = false;
    try
    {
        if (argc >= 2 && strcmp(argv[1], "-debug") == 0)
        { debug = true; }
    }
    catch (...)
    { std::cerr << INVALID_INPUT_PARAMETERS << std::endl; }


    return std::make_shared<CSettings>(CCoord<unsigned int>(1150, 700),
                                       CCoord<unsigned int>(512, 512),
                                       CCoord<unsigned int>(0, 1), 60, true, debug);
}

std::shared_ptr <CWindowManager>
CApplication::GetWindowManagerByState(CSDLInterface *interface, EApplicationStatus applicationStatus) const
{
    switch (applicationStatus)
    {
        case EApplicationStatus::APPLICATION_STATUS_MENU:
            return std::make_shared<CMenuManager>(interface);
        case EApplicationStatus::APPLICATION_STATUS_SETTINGS:
            return std::make_shared<CSettingsManager>(interface);
        case EApplicationStatus::APPLICATION_STATUS_SOLO_GAME:
            return std::make_shared<CGameManager>(interface);
        case EApplicationStatus::APPLICATION_STATUS_MULTI_GAME:
            return std::make_shared<CGameManager>(interface);
        default:
            break;
    }

    throw std::invalid_argument(INVALID_APPLICATION_STATE);
}
