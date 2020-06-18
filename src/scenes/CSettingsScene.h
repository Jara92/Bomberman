/**
 * @author Jaroslav Fikar
 * 
*/

#pragma once
#include "CScene.h"

class CSettingsScene : public CScene
{
public:
    /**
    * Constructor.
    * @param interface Interface to be used.
    */
    explicit CSettingsScene(CSDLInterface &interface);

    virtual ~CSettingsScene() = default;
    CSettingsScene(const CSettingsScene &other) = delete;
    CSettingsScene &operator=(const CSettingsScene &other) = delete;

    virtual EApplicationStatus Run() override ;

    virtual void Init() override
    {}

protected:
    virtual void Draw() const override ;

    virtual void ProcessEvent(SDL_Event & e) override ;

    void UpdateResolution(CCoord <unsigned int>newResolution)
    {
        // Change settings object and reload interface.
        this->m_Interface.GetSettings()->ChangeGameScreenResolution(newResolution);
    }
};

