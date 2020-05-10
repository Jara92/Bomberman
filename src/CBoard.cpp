/**
 * @author Jaroslav Fikar
 * 
*/


#include "CBoard.h"

CBoard::~CBoard()
{
    for(size_t i = 0; i < this->m_BoardSize.m_X; i++){
        for(size_t j = 0; j < this->m_BoardSize.m_X; j++){
            delete this->m_Map[i][j];
        }
        delete [] this->m_Map[i];
    }
    delete [] this->m_Map;
}

bool CBoard::IsPassable(CCoord coord, bool wallPass, bool bombPass, bool firePass)
{
    return false; // TODO
}

void CBoard::Draw(CSDLInterface *interface)
{
    for(size_t i = 0; i < this->m_BoardSize.m_X ; i++){
        for(size_t j = 0; j < this->m_BoardSize.m_Y; j++){
           if(this->m_Map[i][j])  this->m_Map[i][j]->Draw(interface, CCoord(i,j), this->m_CellSize);
        }
    }
}
