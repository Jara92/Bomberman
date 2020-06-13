/**
 * @author Jaroslav Fikar
 * 
*/

#pragma once

#include <memory>
#include "../CSDLInterface.h"
#include "../CTexturePack.h"

class CBoard;

class CBlock
{
public:
    /**
    * Game object contructor
    * @param texturePack Texturepack to be rendered.
    * @param size Object size.
    * @param location Object location.
    */
    CBlock(std::shared_ptr<CTexturePack> texturePack)
    : m_TexturePack(std::move(texturePack))
    {}

    CBlock(const CBlock &other) = default;

    CBlock &operator=(const CBlock &other) = default;

    virtual ~CBlock() = default;

    /**
    * Updates object state using deltatime.
    * @param board Game board
    * @param deltaTime DeltaTime
    */
    void Update(CBoard &board, int deltaTime)
    {}

    /**
     * Draw block.
     * @param interface Interface to be used.
     * @param cellSize Game board cell size.
     * @param location Block location.
     * @param offset Drawing offset.
     */
    void Draw(CSDLInterface &interface, int cellSize, CCoord<> location, CCoord<> offset = CCoord<>(0, 0));

protected:
    std::shared_ptr<CTexturePack> m_TexturePack;
};

