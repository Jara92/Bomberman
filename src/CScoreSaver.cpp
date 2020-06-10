/**
 * @author Jaroslav Fikar
 * 
*/


#include "CScoreSaver.h"

std::size_t CScoreSaver::GetTopScore() const
{
    try
    {
        std::ifstream fileReader(this->m_Settings->GetDataPath() + this->m_ScoreFile, std::ios::in);

        // Is file reader ok?
        if (!fileReader || !fileReader.is_open() || fileReader.eof() || fileReader.bad())
        { throw std::ios::failure(MESSAGE_UNABLE_TO_OPEN_FILE); }

        std::size_t topScore = 0;

        if (!(fileReader >> topScore))
        { throw std::ios::failure(MESSAGE_INVALID_ARGUMENT); }

        fileReader.close();

        return topScore;
    }
    catch (std::exception &ex)
    {
        std::cerr << "Failed to load top score: " << ex.what() << std::endl;
        return 0;
    }
    catch (...)
    { return 0; }
}

/*====================================================================================================================*/
bool CScoreSaver::TrySetTopScore(std::size_t newScore)
{
    try
    {
        if (newScore > this->GetTopScore())
        {
            std::ofstream fileWriter(this->m_Settings->GetDataPath() + this->m_ScoreFile, std::ios::out);

            // Is file writer ok?
            if (!fileWriter || !fileWriter.is_open() || fileWriter.bad())
            { throw std::ios::failure(MESSAGE_UNABLE_TO_OPEN_FILE); }

            if (!(fileWriter << newScore))
            { throw std::ios::failure(MESSAGE_CANNOT_WRITE_TO_FILE); }
        }

        return true;
    }
    catch (std::exception &ex)
    {
        std::cerr << "Failed to save top score: " << ex.what() << std::endl;
        return false;
    }
    catch (...)
    { return false; }
}



