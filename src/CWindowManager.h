/**
 * @author Jaroslav Fikar
 * 
*/

#pragma once
#include "CSDLInterface.h"


class CWindowManager
{
public:
    /**
     * Constructor.
     * @param interface Interface to be used.
     */
    explicit CWindowManager(CSDLInterface *interface)
    : m_Interface(interface)
    {}
    ~CWindowManager() = default;
    CWindowManager (const CWindowManager & other) = delete;
    CWindowManager & operator = (const CWindowManager & other) = delete;

    /**
     * Init window.
     */
    virtual void Init()
    {}

    /**
     * Run window.
     */
    virtual int Run() = 0;

protected:
    CSDLInterface * m_Interface;

    /**
     * Update window state.
     * @param deltaTime Delta time.
     */
    virtual void Update(int deltaTime) = 0;

    /**
     * Check and handle events
     */
    virtual void UpdateEvents() = 0;

    /**
     * Draw window.
     */
    virtual void Draw() const = 0;
};

