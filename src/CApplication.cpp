/**
 * @author Jaroslav Fikar
 * 
*/


#include "CApplication.h"

int CApplication::Run()
{
    CSettings settings (1.3 * 1150,1.3 * 700, CCoord(0,1));
    CSDLInterface interface ("Bomberman", &settings);

    try{
        interface.InitInterface();

        // todo add menu

        CGameManager gameManager(&interface);
        gameManager.Init();

        gameManager.Run();
    }
    catch(std::ios::failure & ex)
    {
        std::cerr << ex.what() << std::endl;
        interface.ShowMessageBox(SDL_MESSAGEBOX_ERROR, MESSAGE_FILESYSTEM_ERROR , ex.what());

        return 1;
    }
    catch(std::exception & ex)
    {
        std::cerr << ex.what() << std::endl;
        interface.ShowMessageBox(SDL_MESSAGEBOX_ERROR, MESSAGE_ERROR , ex.what());

        return 1;
    }

    return 0;
}
