/**
 * @author Jaroslav Fikar
 * 
*/

#pragma once
#include <vector>
#include <memory>
#include "CWindowManager.h"
#include "../interfaceitems/CImage.h"
#include "../interfaceitems/CText.h"
#include "../interfaceitems/CButton.h"

class CMenuManager : public CWindowManager
{
public:
    /**
 * Constructor.
 * @param interface Interface to be used.
 */
    explicit CMenuManager(CSDLInterface *interface);

    ~CMenuManager();
    CMenuManager(const CMenuManager &other) = delete;
    CMenuManager &operator=(const CMenuManager &other) = delete;

    virtual EApplicationStatus Run() override ;

protected:
    bool m_IsRunning;
    EApplicationStatus m_NextApplicationState;

    std::vector<std::unique_ptr<CInterfaceItem>> m_InterfaceItems;

    virtual void Update(int deltaTime) override ;

    virtual void UpdateEvents() override ;

    virtual void Draw() const override ;
};


