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
     * @param gameScreenSize Game screen size in pixels.
     * @param menuScreenSize Menu Screen size in pixels.
     * @param screenFPS Rendered frames per second.
     * @param sound Enable sound?
     * @param debugMode Is debug mode on?
     * @param assetsPath Assets directory path.
     * @param dataPath  Data directory path.
     */
    CSettings(CCoord<unsigned int> gameScreenSize = CCoord<unsigned int>(1150, 600),
              CCoord<unsigned int> menuScreenSize = CCoord<unsigned int>(500, 500),
              CCoord<unsigned int> offset = CCoord<unsigned int>(0, 0),
              unsigned int screenFPS = 60,
              bool sound = true, bool debugMode = false, std::string assetsPath = "./examples/assets/",
              std::string dataPath = "./examples/data/")
            : m_DebugMode(debugMode), m_RenderBoundingBox(false), m_AssetsPath(std::move(assetsPath)), m_DataPath(std::move(dataPath)),
              m_Offset(offset)
    {
        this->ChangeSettings(gameScreenSize, menuScreenSize, sound);
    }

    CSettings(const CSettings &other) = default;

    CSettings &operator=(const CSettings &other) = default;

    ~CSettings() = default;

    /**
     * Change settings.
     * @param newGameScreenSize Game screen size in pixels
     * @param newMenuScreenSize Menu screen size in pixels
     * @param sound Enable sound?
     */
    void ChangeSettings(CCoord<unsigned int> newGameScreenSize, CCoord<unsigned int> newMenuScreenSize, bool sound)
    {
        this->m_GameScreenSize = newGameScreenSize;
        this->m_MenuScreenSize = newMenuScreenSize;

        this->m_Sound = sound;
    }

    void ChangeGameScreenResolution(CCoord<unsigned int> newScreenSize)
    {
        this->m_GameScreenSize = newScreenSize;
    }

    void SetSound(bool sound)
    { this->m_Sound = sound; }

    void SetRenderBoundingBox(bool renderBoundingBox)
    {this->m_RenderBoundingBox = renderBoundingBox;}

    CCoord<unsigned int> GetGameScreenSize() const
    { return this->m_GameScreenSize; }

    CCoord<unsigned int> GetMenuScreenSize() const
    { return this->m_MenuScreenSize; }

    bool GetSound() const
    { return this->m_Sound; }

    bool GetRenderBoundingBox() const
    { return this->m_RenderBoundingBox; }

    bool GetDebugMode() const
    { return this->m_DebugMode; }

    std::string GetAssetsPath() const
    { return this->m_AssetsPath; }

    std::string GetDataPath() const
    { return this->m_DataPath; }

    CCoord<unsigned int> GetOffset() const
    { return this->m_Offset; }

protected:
    CCoord<unsigned int> m_GameScreenSize, m_MenuScreenSize;
    bool m_Sound, m_DebugMode, m_RenderBoundingBox;
    std::string m_AssetsPath, m_DataPath;
    CCoord<unsigned int> m_Offset;
};

