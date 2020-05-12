/**
 * @author Jaroslav Fikar
 * 
*/


#include "CSDLInterface.h"
#include "Messages.h"

CSDLInterface::CSDLInterface()
: m_WindowWidth(0), m_WindowHeight(0), m_Window(nullptr), m_Renderer(nullptr)
{
    // Init SDL
    SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO);

    IMG_Init(IMG_INIT_PNG | IMG_INIT_JPG);

    // Smooth texture rendering
    SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1");
}

CSDLInterface::~CSDLInterface()
{
    // SDL is C library and it uses NULL
    if (this->m_Window != NULL && this->m_Window != nullptr)
    {
        SDL_DestroyWindow(this->m_Window);
    }

    if(this->m_Renderer != NULL && this->m_Renderer != nullptr){
        SDL_DestroyRenderer(this->m_Renderer);
    }

    // Quit SDL
    IMG_Quit();

    SDL_QuitSubSystem(SDL_INIT_EVERYTHING);

     SDL_Quit();
}

bool CSDLInterface::InitInterface(const char *title, CSettings * settings)
{
    this->m_Settings = settings;
    this->m_WindowWidth = settings->GetScreenWidth();
    this->m_WindowHeight = settings->GetScreenHeight();

    // Create an application window with the following settings:
    this->m_Window = SDL_CreateWindow(
            title,                  // window title
            SDL_WINDOWPOS_CENTERED,           // initial x position
            SDL_WINDOWPOS_CENTERED,           // initial y position
            settings->GetScreenWidth(),                               // width, in pixels
            settings->GetScreenHeight(),                               // height, in pixels
            SDL_WINDOW_OPENGL  | SDL_WINDOW_RESIZABLE                // flags - see below
    );

    // Check that the window was successfully created
    if (this->m_Window == NULL)
    {
        // In the case that the window could not be made...
        std::cerr << "Could not create window: \n" <<  SDL_GetError() << std::endl;
        return false;
    }

    // Init renderer
    this->m_Renderer = SDL_CreateRenderer(this->m_Window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_TARGETTEXTURE);

    // Check that the renderer was successfully created
    if (this->m_Window == NULL)
    {
        // In the case that the window could not be made...
        std::cerr << "Could not create renderer: \n" <<  SDL_GetError() << std::endl;
        return false;
    }

    return true;
}

void CSDLInterface::UpdateSettings(CSettings *settings)
{
    this->m_Settings = settings;
    SDL_SetWindowSize(this->m_Window, settings->GetScreenWidth(), settings->GetScreenHeight());
}

SDL_Texture *CSDLInterface::LoadTexture(const std::string & file) const
{
    SDL_Texture * texture = IMG_LoadTexture(this->m_Renderer, (this->m_Settings->GetAssetsPath() + file).c_str());

    if (!texture)
    {
        throw std::ios_base::failure(MESSAGE_TEXTURE_ERROR);
    }

    return texture;
}

void CSDLInterface::ShowMessageBox(Uint32 flags, const std::string title, const std::string message)
{
    SDL_ShowSimpleMessageBox(flags, title.c_str(), message.c_str(), this->m_Window);
}

void CSDLInterface::RenderTexture(SDL_Texture *texture, CCoord location, CCoord size)
{
    SDL_Rect targetRect = {static_cast<int>(location.m_X),static_cast<int>(location.m_Y),
                           static_cast<int>(size.m_X), static_cast<int>(size.m_Y)};

    // TODO Debug
    this->SetRenderColor(0,0,255,255);
   // this->RenderRectangle(&targetRect);
    this->SetRenderColor(255,0,0,255);

    SDL_RenderCopy(this->m_Renderer, texture, NULL, &targetRect);
}
