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
    */
    CBlock(std::shared_ptr<CTexturePack> texturePack, CCoord<> size = {1,1})
    : m_TexturePack(std::move(texturePack)), m_Size(size), m_IsAlive(true)
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

    bool IsAlive() const
    {return this->m_IsAlive;}

protected:
    std::shared_ptr<CTexturePack> m_TexturePack;
    CCoord<> m_Size;
    bool m_IsAlive;
};

