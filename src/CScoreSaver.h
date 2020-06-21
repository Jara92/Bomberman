/**
 * @author Jaroslav Fikar
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
    CScoreSaver(CSettings & settings, std::string scoreFile = "score")
            : m_Settings(settings), m_ScoreFile(std::move(scoreFile))
    {}

    CScoreSaver(const CScoreSaver &other) = delete;

    CScoreSaver &operator=(const CScoreSaver &other) = delete;

    ~CScoreSaver() = default;

    std::size_t GetTopScore() const;

    /**
     * Try save new top score in file if newscore is higher than old topscore.
     * @return True - success
     */
    bool TrySetTopScore(std::size_t newScore);

protected:
    CSettings & m_Settings;
    std::string m_ScoreFile;
};

