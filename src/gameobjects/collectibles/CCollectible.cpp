/**
 * @author Jaroslav Fikar
 *
*/


#include "CCollectible.h"
#include "../../CBoard.h"

void CCollectible::Reset(CBoard &board)
{
    CGameObject::Reset(board);
    this->m_IsVisible = false;

    // Atach this collectible to new existing and destructible Wall which has not collectible yet.
    CCoord<unsigned int> randomWallLocation;
    CWall *randomWall = nullptr;
    do
    {
        randomWallLocation = board.GetRandomBoardLocation();
        randomWall = board.m_Map[randomWallLocation.m_X][randomWallLocation.m_Y];
    } while (!randomWall || !randomWall->IsDestructible() || randomWall->HasCollectible());

    randomWall->AttachCollectible(this);
    this->SetLocation(randomWallLocation.ToDouble());
}