/**
 * @author Jaroslav Fikar
 * 
*/

#pragma once
#include <vector>
#include <memory>
#include "CWindowManager.h"
#include "../CScoreSaver.h"

/** Class which manages menu rendering and user events. */
class CMenuManager : public CWindowManager
{
public:
    /**
    * Constructor.
    * @param interface Interface to be used.
    */
    explicit CMenuManager(CSDLInterface *interface);

    virtual ~CMenuManager() = default;
    CMenuManager(const CMenuManager &other) = delete;
    CMenuManager &operator=(const CMenuManager &other) = delete;

    virtual EApplicationStatus Run() override ;

    virtual void Init() override
    {}

protected:
    std::unique_ptr<CScoreSaver> m_ScoreSaver;

    virtual void Update(int deltaTime) override ;

    virtual void UpdateEvents() override ;

    virtual void ProcessEvent(SDL_Event & e) override ;

    virtual void Draw() const override ;
};


