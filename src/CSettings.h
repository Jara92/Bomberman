/**
 * @author Jaroslav Fikar
 * 
*/

#pragma once

#include <iostream>
#include <vector>
#include "CCoord.h"

class CSettings
{
public:
    /**
     * Initializes a new instance of the CSettings.
     * @param gameScreenWidth Game screen width in pixels
     * @param gameScreenWidth Game Screen height in pixels
     * @param menuScreenWidth Menu screen width in pixels
     * @param menuScreenWidth Menu Screen height in pixels
     * @param screenFPS Rendered frames per second
     * @param sound Enable sound?
     * @param debugMode Is debug mode on?
     * @param assetsPath Assets directory path
     * @param dataPath  Data directory path
     */
    CSettings(unsigned int gameScreenWidth = 1150, unsigned int gameScreenHeight = 600,
              unsigned int menuScreenWidht = 500, unsigned int menuScreenHeight = 500, CCoord offset = CCoord(0, 0),
              unsigned int screenFPS = 60,
              bool sound = true, bool debugMode = false, std::string assetsPath = "./examples/assets/",
              std::string dataPath = "./examples/data/")
            : m_DebugMode(debugMode), m_AssetsPath(std::move(assetsPath)), m_DataPath(std::move(dataPath)),
              m_Offset(offset)
    {
        this->ChangeSettings(gameScreenWidth, gameScreenHeight, menuScreenWidht, menuScreenHeight, sound);
    }

    CSettings(const CSettings &other) = default;

    CSettings &operator=(const CSettings &other) = default;

    ~CSettings() = default;

    /**
     * Change settings.
     * @param width Screen width in pixels
     * @param height Screen height in pixels
     * @param sound Enable sound?
     */
    void ChangeSettings(unsigned int gameScreenWidth, unsigned int gameScreenHeight, unsigned int menuScreenWidth,
                        unsigned int menuScreenHeight, bool sound)
    {
        this->m_GameScreenWidth = gameScreenWidth;
        this->m_GameScreenHeight = gameScreenHeight;

        this->m_MenuScreenWidth = menuScreenWidth;
        this->m_MenuScreenHeight = menuScreenHeight;

        this->m_Sound = sound;
    }

    unsigned int GetGameScreenWidth() const
    { return this->m_GameScreenWidth; }

    unsigned int GetGameScreenHeight() const
    { return this->m_GameScreenHeight; }

    unsigned int GetMenuScreenWidth() const
    { return this->m_MenuScreenWidth; }

    unsigned int GetMenuScreenHeight() const
    { return this->m_MenuScreenHeight; }

    bool GetSound() const
    { return this->m_Sound; }

    bool GetDebugMode() const
    { return this->m_DebugMode; }

    std::string GetAssetsPath() const
    { return this->m_AssetsPath; }

    std::string GetDataPath() const
    { return this->m_DataPath; }

    CCoord GetOffset() const
    { return this->m_Offset; }

protected:
    unsigned int m_GameScreenWidth;
    unsigned int m_GameScreenHeight;

    unsigned int m_MenuScreenWidth;
    unsigned int m_MenuScreenHeight;

    bool m_Sound;
    bool m_DebugMode;

    std::string m_AssetsPath;
    std::string m_DataPath;
    CCoord m_Offset;
};

