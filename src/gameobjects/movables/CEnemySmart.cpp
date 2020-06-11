/**
 * @author Jaroslav Fikar
 * 
*/


#include "CEnemySmart.h"

void CEnemySmart::Update(CBoard *board, int deltaTime)
{
    // Todo Smart enemy AI staff
    // Zde budou volány metody chytrého nepřítele
    CCoord<> newLocation = this->m_Location + (m_Direction * deltaTime * this->m_Speed);
    if (this->m_Direction == CCoord<>(0, 0) || !this->CellIsFree(board, newLocation))
    {
        auto directions = this->GetPossibleMoveDirections(board);

        if (!directions.empty())
        { m_Direction = directions[0].second;     this->m_ActualTexture = directions[0].first;}
        else
        { m_Direction = CCoord<>(0, 0); }

        newLocation = this->m_Location + (m_Direction * deltaTime * this->m_Speed);
    }

    this->m_Location = newLocation;


    auto directions = this->GetPossibleMoveDirections(board);
    if (!directions.empty() && m_Direction == CCoord<>(0, 0))
    {
        // std::cout << "old: " << m_Location << std::endl;
        // m_Direction = directions[0];
        //this->m_Location += (directions[0] * deltaTime * this->m_Speed);
        // std::cout << directions[0].ToDouble() << std::endl;
        //std::cout << m_Location << std::endl;
    }
    //this->m_Location += (m_Direction * deltaTime * this->m_Speed);
    // this->m_Location.m_X += m_Speed * deltaTime;
}

int CEnemySmart::TryKill(unsigned int distance)
{
    // Todo Smart enemy staff
    return 0;
}
