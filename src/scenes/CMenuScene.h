/**
 * @author Jaroslav Fikar
 * 
*/

#pragma once
#include <vector>
#include <memory>
#include "CScene.h"
#include "../CScoreSaver.h"

/** Class which manages menu rendering and user events. */
class CMenuScene : public CScene
{
public:
    /**
    * Constructor.
    * @param interface Interface to be used.
    */
    explicit CMenuScene(CSDLInterface &interface);

    virtual ~CMenuScene() = default;
    CMenuScene(const CMenuScene &other) = delete;
    CMenuScene &operator=(const CMenuScene &other) = delete;

    virtual EApplicationStatus Run() override ;

    virtual void Init() override
    {}

protected:
    virtual void ProcessEvent(SDL_Event & e) override ;

    virtual void Draw() const override ;
};


