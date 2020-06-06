/**
 * @author Jaroslav Fikar
 * 
*/



#include "CSDLInterface.h"


CSDLInterface::CSDLInterface(const char *title, std::shared_ptr<CSettings> settings, const std::string &defaultFont)
        : m_WindowWidth(settings->GetMenuScreenWidth()), m_WindowHeight(settings->GetMenuScreenHeight()),
          m_WindowTitle(title), m_Settings(std::move(settings)), m_Font(defaultFont), m_Window(nullptr),
          m_Renderer(nullptr)
{}

/*====================================================================================================================*/
CSDLInterface::~CSDLInterface()
{
    // SDL is C library and it uses NULL
    if (this->m_Renderer != NULL && this->m_Renderer != nullptr)
    {
        SDL_DestroyRenderer(this->m_Renderer);
    }

    if (this->m_Window != NULL && this->m_Window != nullptr)
    {
        SDL_DestroyWindow(this->m_Window);
    }

    // Quit SDL
    IMG_Quit();
    TTF_Quit();
    SDL_QuitSubSystem(SDL_INIT_EVERYTHING);
    SDL_Quit();
}

/*====================================================================================================================*/
bool CSDLInterface::InitInterface()
{
    int imgFlags = IMG_INIT_PNG | IMG_INIT_JPG;

    // Init SDL
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) < 0 || IMG_Init(imgFlags) != imgFlags ||
        TTF_Init() == -1)
    {
        throw std::runtime_error(SDL_GetError());
    }

    // Smooth texture rendering
    SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1");

    // Create an application window with the following settings:
    this->m_Window = SDL_CreateWindow(
            this->m_WindowTitle,                  // window title
            SDL_WINDOWPOS_CENTERED,           // initial x position
            SDL_WINDOWPOS_CENTERED,           // initial y position
            this->m_WindowWidth,                         // width, in pixels
            this->m_WindowHeight,                               // height, in pixels
            SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE                // flags
    );

    // Check that the window was successfully created
    if (this->m_Window == NULL)
    {
        // In the case that the window could not be made...
        std::cerr << MESSAGE_SDL_WINDOW_ERROR << "\n" << SDL_GetError() << std::endl;
        return false;
    }

    // Init renderer
    this->m_Renderer = SDL_CreateRenderer(this->m_Window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_TARGETTEXTURE |
                                                              SDL_RENDERER_PRESENTVSYNC);

    // Check that the renderer was successfully created
    if (this->m_Window == NULL)
    {
        // In the case that the window could not be made...
        std::cerr << MESSAGE_SDL_RENDERER_ERROR << "\n" << SDL_GetError() << std::endl;
        return false;
    }

    return true;
}

/*====================================================================================================================*/
void CSDLInterface::UpdateSettings(std::shared_ptr<CSettings> settings)
{
    // todo remove
    this->m_Settings = settings;
    SDL_SetWindowSize(this->m_Window, settings->GetGameScreenWidth(), settings->GetGameScreenHeight());
}

/*====================================================================================================================*/
SDL_Texture *CSDLInterface::LoadTexture(const std::string file) const
{
    SDL_Texture *texture = IMG_LoadTexture(this->m_Renderer, (this->m_Settings->GetAssetsPath() + file).c_str());

    if (texture == nullptr || texture == NULL)
    {
        throw std::ios_base::failure(MESSAGE_TEXTURE_ERROR + (this->m_Settings->GetAssetsPath() + file));
    }

    return texture;
}

/*====================================================================================================================*/
void CSDLInterface::ShowMessageBox(Uint32 flags, const std::string &title, const std::string &message)
{
    SDL_ShowSimpleMessageBox(flags, title.c_str(), message.c_str(), this->m_Window);
}

/*====================================================================================================================*/
bool CSDLInterface::RenderTexture(SDL_Texture *texture, CCoord location, CCoord size)
{
    SDL_Rect targetRect = {static_cast<int>(location.m_X), static_cast<int>(location.m_Y),
                           static_cast<int>(size.m_X), static_cast<int>(size.m_Y)};

    // TODO Debug
    this->SetRenderColor(0, 0, 255, 255);
    // this->RenderRectangle(&targetRect);
    this->SetRenderColor(255, 0, 0, 255);

    return SDL_RenderCopy(this->m_Renderer, texture, NULL, &targetRect);
}

/*====================================================================================================================*/
bool CSDLInterface::RenderText(const std::string &text, CCoord location, CCoord size, SDL_Colour color)
{
    TTF_Font *font = TTF_OpenFont((this->m_Settings->GetAssetsPath() + this->m_Font).c_str(), 48);
    if (font == NULL)
    {
        return false;
    }

    SDL_Surface *surfaceMessage = TTF_RenderText_Blended(font, (text).c_str(), color);
    if (surfaceMessage == NULL)
    {
        return false;
    }

    SDL_Texture *message = SDL_CreateTextureFromSurface(this->m_Renderer, surfaceMessage);
    if (message == NULL)
    {
        return false;
    }

    SDL_Rect Message_rect; //create a rect
    Message_rect.x = static_cast<int>(location.m_X);  //controls the rect's x coordinate
    Message_rect.y = static_cast<int>(location.m_Y); // controls the rect's y coordinte
    if (size.m_X != 0)
    {
        Message_rect.w = static_cast<int>(size.m_X);; // controls the width of the rect
    } else
    {
        Message_rect.w = surfaceMessage->w; // controls the width of the rect
    }

    if (size.m_Y != 0)
    {
        Message_rect.h = static_cast<int>(size.m_Y);; // controls the height of the rect
    } else
    {
        Message_rect.h = surfaceMessage->h; // controls the height of the rect
    }

    bool success = SDL_RenderCopy(this->m_Renderer, message, NULL, &Message_rect) >= 0;

    // Free surface and texture
    TTF_CloseFont(font);
    SDL_FreeSurface(surfaceMessage);
    SDL_DestroyTexture(message);

    return success;
}

void CSDLInterface::SetMenuScreenSize()
{
    this->m_WindowWidth = this->m_Settings->GetMenuScreenWidth();
    this->m_WindowHeight = this->m_Settings->GetMenuScreenHeight();

    this->UpdateWindowSize();
}

void CSDLInterface::SetGameScreenSize()
{
    this->m_WindowWidth = this->m_Settings->GetGameScreenWidth();
    this->m_WindowHeight = this->m_Settings->GetGameScreenHeight();

    this->UpdateWindowSize();
}

void CSDLInterface::UpdateWindowSize()
{
    SDL_SetWindowSize(this->m_Window, this->m_WindowWidth, this->m_WindowHeight);
    SDL_SetWindowPosition(this->m_Window, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED);
}

SDL_Texture *CSDLInterface::LoadTextureFromText(const std::string &text, CCoord & size, SDL_Color color) const
{
    TTF_Font *font = TTF_OpenFont((this->m_Settings->GetAssetsPath() + this->m_Font).c_str(), 48);
    if (font == NULL)
    {
        return NULL;
    }

    SDL_Surface *surfaceMessage = TTF_RenderText_Blended(font, (text).c_str(), color);
    if (surfaceMessage == NULL)
    {
        return NULL;
    }

    SDL_Texture *message = SDL_CreateTextureFromSurface(this->m_Renderer, surfaceMessage);
    if (message == NULL)
    {
        return NULL;
    }

    // Set size
    // TODO předělat na konstruktor
    size.m_X = surfaceMessage->w;
    size.m_Y = surfaceMessage->h;

    // Free surface and texture
    TTF_CloseFont(font);
    SDL_FreeSurface(surfaceMessage);

    return message;
}
