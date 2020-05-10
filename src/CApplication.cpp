/**
 * @author Jaroslav Fikar
 * 
*/


#include "CApplication.h"

int CApplication::Run()
{
    CSettings settings (1200,650, true);
    CSDLInterface interface;

    if(!interface.InitInterface("Bomberman", &settings)){
        std::cerr << MESSAGE_SDL_WINDOW_ERROR << std::endl;
        return 1;
    }

    try{
        // todo add menu

        CGameManager gameManager(&interface);
        gameManager.Init();

        gameManager.Run();
    }
    catch(std::ios::failure ex){
        std::cerr << ex.what() << std::endl;
        interface.ShowMessageBox(SDL_MESSAGEBOX_ERROR, MESSAGE_FILESYSTEM_ERROR , ex.what());

        return 1;
    }

    return 0;
}
