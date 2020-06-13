/**
 * @author Jaroslav Fikar
*/

#include "CWall.h"

bool CWall::TryDestroy(unsigned int distance)
{
    if (this->m_IsDestructible)
    {
        if (this->m_Collectible)
        { this->m_Collectible->MakeVisible(); }
        /* This is not MEMLEAK. Another pointer to this object is in the Board.
        * This pointer is saved to call MakeVisible() method when the wall is being destroyed.
        * Destroyed object has no reason to have this pointer.
        */
        this->m_Collectible = nullptr;

        this->m_IsAlive = false;

        return true;
    }

    return false;
}

void CWall::Draw(CSDLInterface *interface, int cellSize, CCoord<> location, CCoord<> offset)
{
    // Create texture offset to target cell.
    CCoord<> textureOffset = CCoord<>((1 - this->m_TexturePack->GetTextureSize().m_X),
                                      (1 - this->m_TexturePack->GetTextureSize().m_Y));

    // Center texture position if required.
    if (this->m_TexturePack->IsCentered())
    { textureOffset /= 2; }

    unsigned int index = 0;

    // Setup final location and draw texture in right position.
    location = location + textureOffset + offset;
    interface->RenderTexture(this->m_TexturePack->GetTexture(ETextureType::TEXTURE_FRONT, &index),
                             CCoord<>(location.m_X * cellSize, location.m_Y * cellSize),
                             cellSize * this->m_TexturePack->GetTextureSize());
}
