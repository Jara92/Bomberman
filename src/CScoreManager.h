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
    CScoreManager(/*CSettings *settings*/)
           /* : m_Settings(settings)*/
    {}

    CScoreManager(const CScoreManager &other) = default;

    CScoreManager &operator=(const CScoreManager &other) = default;

    ~CScoreManager() = default;


    unsigned int GetTopScore() const;

    /**
     * Try save new top score in file if newscore is higher than old topscore.
     * @return True - success
     */
    bool TrySetTopScore(std::size_t newScore);

protected:
    static const std::string TOP_SCORE_FILE_NAME;
 //   CSettings *m_Settings;
};

