/**
 * @author Jaroslav Fikar
 * 
*/

#pragma once

#include "CWindowManager.h"

class CMenuManager : public CWindowManager
{
public:
    /**
 * Constructor.
 * @param interface Interface to be used.
 */
    explicit CMenuManager(CSDLInterface *interface)
            : CWindowManager(interface), m_IsRunning(true)
    {}

    ~CMenuManager() = default;
    CMenuManager(const CMenuManager &other) = delete;
    CMenuManager &operator=(const CMenuManager &other) = delete;

    virtual int Run() override ;

protected:
    bool m_IsRunning;

    virtual void Update(int deltaTime) override ;

    virtual void UpdateEvents() override ;

    virtual void Draw() const override ;
};


