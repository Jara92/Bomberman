/**
 * @author Jaroslav Fikar
 * 
*/

#pragma once

#include <iostream>
#include <fstream>
#include <memory>
#include "CSettings.h"
#include "Messages.h"

class CScoreSaver
{
public:
    CScoreSaver(std::shared_ptr<CSettings> settings, const std::string &scoreFile = "score")
            : m_Settings(std::move(settings)), m_ScoreFile(scoreFile)
    {}

    CScoreSaver(const CScoreSaver &other) = default;

    CScoreSaver &operator=(const CScoreSaver &other) = default;

    ~CScoreSaver() = default;

    std::size_t GetTopScore() const;

    /**
     * Try save new top score in file if newscore is higher than old topscore.
     * @return True - success
     */
    bool TrySetTopScore(std::size_t newScore);

protected:
    std::shared_ptr<CSettings> m_Settings;
    std::string m_ScoreFile;
};

