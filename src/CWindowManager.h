/**
 * @author Jaroslav Fikar
 * 
*/

#pragma once
#include "CSDLInterface.h"
#include "EApplicationStatus.h"
#include "CGameClock.h"


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
    virtual EApplicationStatus Run();

protected:
    CSDLInterface * m_Interface;
    CGameClock m_Clock;

    bool IsClosed() const;

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

