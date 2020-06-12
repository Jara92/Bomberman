/**
 * @author Jaroslav Fikar
*/

#include "CEnemy.h"
#include "../../CBoard.h"

std::vector<std::pair<ETextureType, CCoord<double>>> CEnemy::GetPossibleMoveDirections(CBoard *board)
{
    CCoord<> oldLocation = this->m_Location;

    CCoord<> center = CCoord<>(this->m_Location.m_X + 0.5, this->m_Location.m_Y + 0.5);


    std::vector<std::pair<ETextureType, CCoord<double>>> outputDirections;
    // Create directional vectors and texture types.
    double correction = (1 - this->m_Speed);
    std::vector<std::pair<ETextureType, CCoord<>>> directions = {{ETextureType::TEXTURE_FRONT, CCoord<double>(0,
                                                                                                              correction)},
                                                                 {ETextureType::TEXTURE_BACK,  CCoord<double>(0,
                                                                                                              -correction)},
                                                                 {ETextureType::TEXTURE_RIGHT, CCoord<double>(
                                                                         correction, 0)},
                                                                 {ETextureType::TEXTURE_LEFT,  CCoord<double>(
                                                                         -correction, 0)}};
    // Test every directional vector.
    std::cout << "Avaibles:=================" << std::endl;
    for (unsigned int i = 0; i < directions.size(); i++)
    {
       // this->m_Location = this->m_Location;//; + (directions[i].second);
     //   CCoord<> cell = center + directions[i].second;
       // this->m_Location = cell - CCoord<>(0.5,0.5);

        if(this->CellIsFree(board, this->m_Location))
        {
            outputDirections.push_back(directions[i]);
            std::cout << "avaible: " << directions[i].second << std::endl;
        }

       /* if (this->CellIsFree(board, cell))
        { }*/

        this->m_Location = oldLocation;
    }



    return outputDirections;
}

bool CEnemy::CellIsFree(CBoard *board, CCoord<> location) const
{
    return CMovable::CellIsFree(board, location);
}

bool CEnemy::FreeCell(CBoard *board, CCoord<> newLocation)
{
    CCoord<> diff = this->m_Location - newLocation;




}

CCoord<> CEnemy::FindWayOut(CBoard *board)
{
    return CCoord<>(0, -1);
}
