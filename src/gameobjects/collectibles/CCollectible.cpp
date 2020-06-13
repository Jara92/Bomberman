/**
 * @author Jaroslav Fikar
 *
*/


#include "CCollectible.h"
#include "../../CBoard.h"

void CCollectible::Reset(CBoard &board)
{
    CGameObject::Reset(board);

    // Atach this collectible to new Wall.
    CWall *randomWall = nullptr;
    do
    {
        CCoord<unsigned int> randomWallLocation = board.GetRandomBoardLocation();
        randomWall = board.m_Map[randomWallLocation.m_X][randomWallLocation.m_Y];
    } while (!randomWall || !randomWall->IsDestructible() || !randomWall->HasCollectible());
    randomWall->AttachCollectible(this);
}