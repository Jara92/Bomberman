/**
 * @author Jaroslav Fikar
 * 
*/


#include "CBoard.h"

CBoard::~CBoard()
{
    for (size_t i = 0; i < this->m_BoardSize.m_X; i++)
    {
        for (size_t j = 0; j < this->m_BoardSize.m_Y; j++)
        {
            delete this->m_Map[i][j];
        }
        delete[] this->m_Map[i];
    }
    delete[] this->m_Map;

    for (size_t i = 0; i < this->m_Players.size(); i++)
    {
        delete this->m_Players[i];
    }
}

/*====================================================================================================================*/
bool CBoard::IsPassable(CCoord coord, bool wallPass, bool bombPass, bool firePass)
{
    if (coord.m_X < 0 || coord.m_X >= CBoard::m_BoardSize.m_X ||
        coord.m_Y < 0 || coord.m_Y >= CBoard::m_BoardSize.m_Y)
    {
        throw std::out_of_range(MESSAGE_INDEX_OUT_OF_BOUND);
    }

    CGameObject *gameObject = this->m_Map[static_cast<int>(floor(coord.m_X))][static_cast<int>( floor(coord.m_Y))];

    if (gameObject && gameObject->IsAlive())
    {
        return false;
    }
    return true;
    // todo other gameobjests
}

/*====================================================================================================================*/
void CBoard::DetonateBombs(CPlayer *player)
{

}

/*====================================================================================================================*/
void CBoard::Draw(CSDLInterface *interface)
{
    // TODO debug

    // Draw debug lines
  /*  interface->SetRenderColor(128, 0, 0, 255);
    for (double i = 0; i < interface->GetWindowSize().m_Y; i++)
    {
        interface->RenderLine(CCoord(0, 25 * i), CCoord(interface->GetWindowSize().m_X, 25 * i));
    }

    for (double i = 0; i < interface->GetWindowSize().m_X - 1; i++)
    {
        interface->RenderLine(CCoord(25 * i, 0), CCoord(25 * i, interface->GetWindowSize().m_Y));
    }*/

    // draw map
    for (size_t i = 0; i < this->m_BoardSize.m_X; i++)
    {
        for (size_t j = 0; j < this->m_BoardSize.m_Y; j++)
        {
            if (this->m_Map[i][j]) this->m_Map[i][j]->Draw(interface, this->m_CellSize, CCoord(i, j));
        }
    }

    // draw players
    for (size_t i = 0; i < this->m_Players.size(); i++)
    {
        this->m_Players[i]->Draw(interface, this->m_CellSize);
    }
}

/*====================================================================================================================*/
void CBoard::Update(int deltaTime)
{
    for (size_t i = 0; i < this->m_BoardSize.m_X; i++)
    {
        for (size_t j = 0; j < this->m_BoardSize.m_Y; j++)
        {
            // Update if object is alive
            if (this->m_Map[i][j] && this->m_Map[i][j]->IsAlive())
            {
                this->m_Map[i][j]->Update(this, deltaTime);
            }
                // destroy if is dead (TODO this will be problem with dying animations)
            else
            {
                delete this->m_Map[i][j];
            }
        }
    }

    for (size_t i = 0; i < this->m_Players.size(); i++)
    {
        this->m_Players[i]->Update(this, deltaTime);
    }
}
