/**
 * @author Jaroslav Fikar
 * 
*/

#pragma once

#include <iostream>
#include <memory>
#include <SDL2/SDL.h>
#include <SDL2/SDL_system.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include "CCoord.h"
#include "CSettings.h"
#include "Messages.h"


/**
 * Class which manages SDL resources.
 */
class CSDLInterface
{
public:
    /**
     * Constructor.
     * @param title Window title.
     * @param settings Setting to be used.
     */
    CSDLInterface(const char *title, std::shared_ptr<CSettings> settings, const std::string & defaultFont);
    CSDLInterface(const CSDLInterface &other) = default;
    CSDLInterface & operator=(const CSDLInterface &other) = default;

    ~CSDLInterface();

    /**
     * This functions inits main game Window.
     * @return True - Success
     */
    bool InitInterface();

    void ReloadSettings()
    {

    }

    /**
     * Change settings.
     * @param settings New settings
     */
    void UpdateSettings(std::shared_ptr<CSettings> settings);

    /**
     * Set window size for Menu.
     */
    void SetMenuScreenSize();

    /**
     * Set window size for Game.
     */
    void SetGameScreenSize();

    /**
     * Update window size according to m_WindowWidth and m_WindowHeight and center it.
     */
    void UpdateWindowSize();

    CCoord<unsigned int> GetWindowSize() const
    { return {(m_WindowWidth), (m_WindowHeight)}; }

    std::shared_ptr<CSettings> GetSettings()
    {
        return this->m_Settings;
    }

    /**
     * Load an image into a render texture
     * @param file  File path
     * @throws std::ios_base::failure If texture is not avaible.
     * @return Texture pointer.
     */
    SDL_Texture *LoadTexture(const std::string file) const;

    SDL_Texture *LoadTextureFromText(const std::string & text, CCoord<unsigned int> & size, SDL_Colour color = {255,255,255,255}) const;

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

    /**
     * Render texture.
     * @param texture Texture
     * @param location Render location
     * @param size Texture size
     */
    bool RenderTexture(SDL_Texture *texture, CCoord <> location, CCoord<> size);

    /**
     * Draw a rectangle on the current rendering target.
     * @param rect Rectangle
     */
    void RenderRectangle(SDL_Rect *rect)
    { SDL_RenderDrawRect(this->m_Renderer, rect); }

    /**
     * Draw a line on the current rendering target.
     * @param a First point
     * @param b Second point
     */
    void RenderLine(CCoord<> a, CCoord<> b)
    { SDL_RenderDrawLine(this->m_Renderer, a.m_X, a.m_Y, b.m_X, b.m_Y); }


    bool RenderText(const std::string & text, CCoord <>location, CCoord <>size = CCoord<>(0,0), SDL_Colour color = {255,255,255,255} );

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
    *  Create a modal message box
    *  @param flags    ::SDL_MessageBoxFlags
    *  @param title    UTF-8 title text
    *  @param message  UTF-8 message text
    */
    void ShowMessageBox(Uint32 flags, const std::string &title, const std::string &message);
    /**
     * Wait a specified number of milliseconds before returning.
     * @param time Waiting time in milliseconds.
     */
    void Wait(Uint32 time)
    {SDL_Delay(time);}

protected:
    unsigned int m_WindowWidth;
    unsigned int m_WindowHeight;
    const char * m_WindowTitle;

    std::shared_ptr<CSettings> m_Settings;
    std::string m_Font;
    SDL_Window *m_Window;
    SDL_Renderer *m_Renderer;
};

