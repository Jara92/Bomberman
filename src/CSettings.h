/**
 * @author Jaroslav Fikar
 * 
*/

#pragma once

#include <iostream>

class CSettings
{
public:
    /**
     * Initializes a new instance of the CSettings.
     * @param width Screen width in pixels
     * @param height Screen height in pixels
     * @param screenFPS Rendered frames per second
     * @param sound Enable sound?
     * @param debugMode Is debug mode on?
     * @param assetsPath Assets directory path
     * @param dataPath  Data directory path
     */
    CSettings(std::size_t width = 1150, std::size_t height = 600, size_t screenFPS = 60, bool sound = true,
              bool debugMode = false, std::string assetsPath = "./examples/assets/",
              std::string dataPath = "./examples/data/")
            : m_TicksPerFrame(1000 / screenFPS), m_DebugMode(debugMode), m_AssetsPath(std::move(assetsPath)),
              m_DataPath(std::move(dataPath))
    { this->ChangeSettings(width, height, sound); }

    CSettings(const CSettings &other) = default;

    CSettings &operator=(const CSettings &other) = default;

    ~CSettings() = default;

    /**
     * Change settings.
     * @param width Screen width in pixels
     * @param height Screen height in pixels
     * @param sound Enable sound?
     */
    void ChangeSettings(std::size_t width, std::size_t height, bool sound)
    {
        this->m_ScreenWidth = width;
        this->m_ScreenHeight = height;
        this->m_Sound = sound;
    }

    std::size_t GetScreenWidth() const
    {
        return this->m_ScreenWidth;
    }

    std::size_t GetScreenHeight() const
    {
        return this->m_ScreenHeight;
    }

    std::size_t GetTicksPerFrame() const
    { return this->m_TicksPerFrame; }

    bool GetSound() const
    { return this->m_Sound; }

    bool GetDebugMode() const
    { return this->m_DebugMode; }

    std::string GetAssetsPath() const
    { return this->m_AssetsPath; }

    std::string GetDataPath() const
    { return this->m_DataPath; }

protected:
    std::size_t m_ScreenWidth;
    std::size_t m_ScreenHeight;
    std::size_t m_TicksPerFrame;
    bool m_Sound;
    bool m_DebugMode;

    std::string m_AssetsPath;
    std::string m_DataPath;
};

