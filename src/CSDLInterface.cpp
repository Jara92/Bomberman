/**
 * @author Jaroslav Fikar
*/

#include "CSDLInterface.h"

CSDLInterface::~CSDLInterface()
{
    // SDL is C library and it uses NULL
    if (this->m_Renderer != NULL && this->m_Renderer != nullptr)
    { SDL_DestroyRenderer(this->m_Renderer); }

    if (this->m_Window != NULL && this->m_Window != nullptr)
    { SDL_DestroyWindow(this->m_Window); }

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
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) < 0 || IMG_Init(imgFlags) != imgFlags || TTF_Init() == -1)
    { throw std::runtime_error(SDL_GetError()); }

    // Smooth texture rendering
    SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1");

    // Create an application window with the following settings:
    this->m_Window = SDL_CreateWindow(
            this->m_WindowTitle.c_str(),       // window title
            SDL_WINDOWPOS_CENTERED,              // initial x position
            SDL_WINDOWPOS_CENTERED,              // initial y position
            this->m_WindowSize.m_X,                // width, in pixels
            this->m_WindowSize.m_Y,                // height, in pixels
            SDL_WINDOW_OPENGL                 // flags
    );

    // Check that the window was successfully created
    if (this->m_Window == NULL)
    { throw std::runtime_error(std::string(MESSAGE_SDL_WINDOW_ERROR) + "\n" + SDL_GetError()); }

    // Init renderer
    this->m_Renderer = SDL_CreateRenderer(this->m_Window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_TARGETTEXTURE |
                                                              SDL_RENDERER_PRESENTVSYNC);

    // Check that the renderer was successfully created
    if (this->m_Window == NULL)
    { throw std::runtime_error(std::string(MESSAGE_SDL_RENDERER_ERROR) + "\n" + SDL_GetError()); }

    return true;
}

/*====================================================================================================================*/
SDL_Texture *CSDLInterface::LoadTexture(const std::string &file) const
{
    SDL_Texture *texture = IMG_LoadTexture(this->m_Renderer, (this->m_Settings.GetAssetsPath() + file).c_str());

    if (texture == nullptr || texture == NULL)
    {
        throw std::ios_base::failure(
                MESSAGE_TEXTURE_ERROR + (this->m_Settings.GetAssetsPath() + file) + "\n" + SDL_GetError());
    }

    return texture;
}

/*====================================================================================================================*/
void CSDLInterface::SetMenuScreenSize()
{
    // Change window size if new size is different.
    if (this->m_WindowSize.m_X != this->m_Settings.GetMenuScreenSize().m_X ||
        this->m_WindowSize.m_Y != this->m_Settings.GetMenuScreenSize().m_Y)
    {
        this->m_WindowSize.m_X = this->m_Settings.GetMenuScreenSize().m_X;
        this->m_WindowSize.m_Y = this->m_Settings.GetMenuScreenSize().m_Y;

        this->UpdateWindowSize();
    }
}

/*====================================================================================================================*/
void CSDLInterface::SetGameScreenSize()
{
    // Change window size if new size is different.
    if (this->m_WindowSize.m_X != this->m_Settings.GetGameScreenSize().m_X ||
        this->m_WindowSize.m_Y != this->m_Settings.GetGameScreenSize().m_Y)
    {
        this->m_WindowSize.m_X = this->m_Settings.GetGameScreenSize().m_X;
        this->m_WindowSize.m_Y = this->m_Settings.GetGameScreenSize().m_Y;

        this->UpdateWindowSize();
    }
}

/*====================================================================================================================*/
SDL_Texture *
CSDLInterface::LoadTextTexture(const std::string &text, CCoord<unsigned int> &size, SDL_Color color, int quality) const
{
    // Load font.
    TTF_Font *font = TTF_OpenFont((this->m_Settings.GetAssetsPath() + this->m_Font).c_str(), quality);
    if (font == NULL)
    { return NULL; }

    // Create text surface.
    SDL_Surface *surfaceMessage = TTF_RenderText_Blended(font, (text).c_str(), color);
    if (surfaceMessage == NULL)
    { return NULL; }

    // Create texture.
    SDL_Texture *message = SDL_CreateTextureFromSurface(this->m_Renderer, surfaceMessage);
    if (message == NULL)
    { return NULL; }

    // Set size
    size = CCoord<unsigned int>(surfaceMessage->w, surfaceMessage->h);

    // Free surface and texture
    TTF_CloseFont(font);
    SDL_FreeSurface(surfaceMessage);

    return message;
}
