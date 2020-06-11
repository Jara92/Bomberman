/**
 * @author Jaroslav Fikar
*/

#include "CEnemy.h"
#include "../../CBoard.h"

std::vector<std::pair<ETextureType, CCoord<double>>> CEnemy::GetPossibleMoveDirections(CBoard *board) const
{
    std::vector<std::pair<ETextureType, CCoord<double>>> outputDirections;
    // Create direction vectors.
    double correction = (1 - this->m_Speed);
   /* CCoord<double> directions[4] = {CCoord<double>(0, correction), CCoord<double>(0, -correction),
                                    CCoord<double>(correction, 0), CCoord<double>(-correction, 0)};*/
   std::vector<std::pair<ETextureType, CCoord<>>> directions = {{ETextureType ::TEXTURE_FRONT, CCoord<double>(0, correction)},
                                                  {ETextureType ::TEXTURE_BACK, CCoord<double>(0, -correction)},
                                                  {ETextureType ::TEXTURE_RIGHT, CCoord<double>(correction, 0)},
                                                  {ETextureType ::TEXTURE_LEFT, CCoord<double>(-correction, 0)}};

    //std::cout << "avaible items for location: " << m_Location << std::endl;
    for (unsigned int i = 0; i < directions.size(); i++)
    {
      //  std::cout << this->m_Location << std::endl;
      //  std::cout << (this->m_Location + directions[i]).ToUnsignedInt() << std::endl;
        if (this->CellIsFree(board, this->m_Location + directions[i].second))
        {
            //std::cout << "avaible: " << directions[i] << std::endl;
            outputDirections.push_back(directions[i]);
        }
        else
        {
           // std::cout << "not avaible: " << directions[i] << std::endl;
        }
    }

    return outputDirections;
}

void CEnemy::ChooseAnimation()
{

}
