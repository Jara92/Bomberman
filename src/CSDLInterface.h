/**
 * @author Jaroslav Fikar
 * 
*/

#pragma once

#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_system.h>
#include <SDL2/SDL_image.h>
#include "CCoord.h"
#include "CSettings.h"

/**
 * Class which manages SDL resources.
 */
class CSDLInterface
{
public:
    CSDLInterface();

    CSDLInterface(const CSDLInterface &other) = delete;

    CSDLInterface operator=(const CSDLInterface &other) = delete;

    ~CSDLInterface();

    /**
     * This functions inits main game Window.
     * @param title Window title
     * @param width Window width in pixels
     * @param height Window height in pixels
     * @return True - Success
     */
    bool InitInterface(const char *title, CSettings *settings);

    void UpdateSettings(CSettings *settings);

    SDL_Window *GetWindow() const
    { return this->m_Window; }

    SDL_Renderer *GetRenderer() const
    { return this->m_Renderer; }

    CCoord GetWindowSize() const
    { return CCoord(m_WindowWidth, m_WindowHeight); }

    CSettings *GetSettings()
    {
        return this->m_Settings;
    }

    SDL_Texture *LoadTexture(const std::string & path) const;

    /**
     * Clear the current rendering target with the drawing color
     */
    void Clear()
    { SDL_RenderClear(this->m_Renderer); }

    /**
     * Update the screen with rendering performed.
     */
    void Present()
    { SDL_RenderPresent(this->m_Renderer); }

    void RenderTexture(SDL_Texture *texture, CCoord coord, CCoord size);

    /**
     * Draw a line on the current rendering target.
     * @param a First point
     * @param b Second point
     */
    void RenderLine(CCoord a, CCoord b)
    { SDL_RenderDrawLine(this->m_Renderer, a.m_X, a.m_Y, b.m_X, b.m_Y); }

    /**
    *  Set the color used for drawing operations (Rect, Line and Clear).
    *  @param r The red value used to draw on the rendering target.
    *  @param g The green value used to draw on the rendering target.
    *  @param b The blue value used to draw on the rendering target.
    *  @param a The alpha value used to draw on the rendering target, usually
    */
    void SetRenderColor(Uint8 r, Uint8 g, Uint8 b, Uint8 a)
    { SDL_SetRenderDrawColor(this->m_Renderer, r, g, b, a); }

    /**
    *  Create a simple modal message box
    *
    *  @param flags    ::SDL_MessageBoxFlags
    *  @param title    UTF-8 title text
    *  @param message  UTF-8 message text
    */
    void ShowMessageBox(Uint32 flags, const std::string title, const std::string message);

protected:
    size_t m_WindowWidth;
    size_t m_WindowHeight;

    CSettings *m_Settings;
    SDL_Window *m_Window;
    SDL_Renderer *m_Renderer;
};

