/**
 * @author Jaroslav Fikar
 * 
*/

#pragma once

#include <iostream>
#include <fstream>
#include "CSettings.h"

class CScoreManager
{
public:
    CScoreManager(CSettings *settings)
            : m_Settings(settings)
    {}

    CScoreManager(const CScoreManager &other) = default;

    CScoreManager &operator=(const CScoreManager &other) = default;

    ~CScoreManager() = default;


    unsigned int GetTopScore() const;

    /**
     * Save new top score in file.
     * @return True - success
     */
    bool SetTopScore();

protected:
    static const std::string TOP_SCORE_FILE_NAME;
    CSettings *m_Settings;
};

