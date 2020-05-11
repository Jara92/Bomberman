/**
 * @author Jaroslav Fikar
 * 
*/

#pragma once

#include <iostream>

class CSettings
{
public:
    CSettings &settings(const CSettings &other) = delete;

    CSettings &operator=(const CSettings &other) = delete;

    ~CSettings() = default;

    CSettings(std::size_t width = 1150, std::size_t height = 650, bool sound = false, std::string assetsPath = "./examples/assets/",
              std::string dataPath = "./examples/data/")
            : m_AssetsPath(std::move(assetsPath)), m_DataPath(std::move(dataPath))
    { this->ChangeSettings(width, height, sound); }

    void ChangeSettings(std::size_t width, std::size_t height, bool sound)
    {
        this->m_ScreenWidth = width;
        this->m_ScreenHeight = height;
        this->m_Sound = sound;
    }

    size_t GetScreenWidth() const
    {
        return m_ScreenWidth;
    }

    size_t GetScreenHeight() const
    {
        return m_ScreenHeight;
    }

    bool GetSound() const
    {
        return m_Sound;
    }

    std::string GetAssetsPath() const
    { return this->m_AssetsPath; }

    std::string GetDataPath() const
    { return this->m_DataPath; }

protected:
    std::size_t m_ScreenWidth;
    std::size_t m_ScreenHeight;
    bool m_Sound;

    std::string m_AssetsPath;
    std::string m_DataPath;
};

