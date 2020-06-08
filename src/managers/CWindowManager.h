/**
 * @author Jaroslav Fikar
 * 
*/

#pragma once
#include <memory>
#include <queue>
#include "../CSDLInterface.h"
#include "../EApplicationStatus.h"
#include "../CGameClock.h"
#include "../interfaceitems/CImage.h"
#include "../interfaceitems/CText.h"
#include "../interfaceitems/CButton.h"
#include "../interfaceitems/CInterfaceItem.h"
#include "../interfaceitems/CSelectBox.h"

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
    virtual ~CWindowManager() = default;
    CWindowManager (const CWindowManager & other) = delete;
    CWindowManager & operator = (const CWindowManager & other) = delete;

    /**
     * Run window.
     */
    virtual EApplicationStatus Run();

    virtual void Init() = 0;

protected:
    CSDLInterface * m_Interface;
    /** Interface items in the view. */
    std::vector<std::unique_ptr<CInterfaceItem>> m_InterfaceItems;
    EApplicationStatus m_NextApplicationState;
    /** Application refresh clock. */
    CGameClock m_Clock;

    /**
     * Update window state.
     * @param deltaTime Delta time.
     */
    virtual void Update(int deltaTime);

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
    virtual void Draw() const;
};

