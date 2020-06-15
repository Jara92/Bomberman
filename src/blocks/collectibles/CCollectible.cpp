/**
 * @author Jaroslav Fikar
 *
*/


#include "CCollectible.h"
#include "../../CBoard.h"

void CCollectible::NextLevel(CBoard &board, bool clearLevelObjects)
{
    if (clearLevelObjects)
    {
        this->m_IsDestroyed = true;
        std::cout << "collectible destroyed" << std::endl;
    } else
    {
        this->m_IsVisible = false;

        // Atach this collectible to new existing and destructible Wall which has not collectible yet.
        CCoord<unsigned int> randomWallLocation;
        CBlock *randomWall = nullptr;
        do
        {
            randomWallLocation = board.GetRandomBoardLocation();
            randomWall = board.GetMapItem(randomWallLocation);
        } while (!randomWall || !randomWall->IsExplodable() || randomWall->HasCollectible());

        randomWall->AttachCollectible(this);
    }
}
