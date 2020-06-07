/**
 * @author Jaroslav Fikar
 * 
*/

#pragma once
#include <memory>
#include "../CSDLInterface.h"
#include "../EApplicationStatus.h"
#include "../CGameClock.h"

/**
 * Class which manages content rendering.
 */
class CWindowManager
{
public:
    /**
     * Constructor.
     * @param interface Interface to be used.
     */
    explicit CWindowManager(CSDLInterface *interface)
    : m_Interface(interface), m_NextApplicationState(EApplicationStatus::APPLICATON_STATUS_NONE)
    {}
    ~CWindowManager() = default;
    CWindowManager (const CWindowManager & other) = delete;
    CWindowManager & operator = (const CWindowManager & other) = delete;

    /**
     * Run window.
     */
    virtual EApplicationStatus Run();

protected:
    CSDLInterface * m_Interface;
    EApplicationStatus m_NextApplicationState;
    CGameClock m_Clock;

    /**
     * Update window state.
     * @param deltaTime Delta time.
     */
    virtual void Update(int deltaTime) = 0;

    /**
     * Check and handle events
     */
    virtual void UpdateEvents();

    /**
     * Proccess event by type.
     * @param e Event.
     * @return Next application state.
     */
    virtual void ProcessEvent(SDL_Event & e);

    /**
     * Draw window.
     */
    virtual void Draw() const = 0;
};

