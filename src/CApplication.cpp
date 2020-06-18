/**
 * @author Jaroslav Fikar
 * 
*/


#include "CApplication.h"

int CApplication::Run(int argc, char *argv[])
{
    std::shared_ptr<CSettings> settings = this->Init(argc, argv);
    CSDLInterface interface ("Bomberman", settings,"Fonts/Piedra-Regular.ttf");
    try
    {
        // ToDO poladit, aby při chybě načtení SDL nebylo voláno okno show message box
        if (interface.InitInterface())
        {
            EApplicationStatus applicationStatus = EApplicationStatus::APPLICATION_STATUS_SOLO_GAME;
            //EApplicationStatus applicationStatus = EApplicationStatus::APPLICATION_STATUS_MENU;

            // Run manager while application is running and get next application state.
            while (applicationStatus != EApplicationStatus::APPLICATION_STATUS_EXIT)
            { applicationStatus = this->GetWindowManagerByState(interface, applicationStatus)->Run(); }
        }
    }
    catch (std::ios::failure &ex)
    {
        std::cerr << ex.what() << std::endl;
        interface.ShowMessageBox(SDL_MESSAGEBOX_ERROR, MESSAGE_FILESYSTEM_ERROR, ex.what());
        return 1;
    }
    catch (std::exception &ex)
    {
        std::cerr << ex.what() << std::endl;
        interface.ShowMessageBox(SDL_MESSAGEBOX_ERROR, MESSAGE_UNKNOWN_ERROR, ex.what());
        return 1;
    }
    catch (...)
    {
        std::cerr << MESSAGE_UNKNOWN_ERROR << std::endl;
        interface.ShowMessageBox(SDL_MESSAGEBOX_ERROR, MESSAGE_UNKNOWN_ERROR, MESSAGE_UNKNOWN_ERROR);
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
        { debug = true; }
    }
    catch (...)
    { std::cerr << MESSAGE_INVALID_INPUT_PARAMETERS << std::endl; }

    // TODO REMOVE
    debug = true;

    return std::make_shared<CSettings>(CCoord<unsigned int>(1495, 910),
                                       CCoord<unsigned int>(512, 512),
                                       CCoord<unsigned int>(0, 1), 60, true, debug);
}

std::shared_ptr<CScene>
CApplication::GetWindowManagerByState(CSDLInterface &interface, EApplicationStatus applicationStatus) const
{
    switch (applicationStatus)
    {
        case EApplicationStatus::APPLICATION_STATUS_MENU:
            return std::make_shared<CMenuScene>(interface);
        case EApplicationStatus::APPLICATION_STATUS_SETTINGS:
            return std::make_shared<CSettingsScene>(interface);
        case EApplicationStatus::APPLICATION_STATUS_SOLO_GAME:
            return std::make_shared<CGameScene>(interface);
        case EApplicationStatus::APPLICATION_STATUS_MULTI_GAME:
            return std::make_shared<CGameScene>(interface);
        default:
            throw std::invalid_argument(MESSAGE_INVALID_APPLICATION_STATE);
    }
}
