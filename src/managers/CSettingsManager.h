/**
 * @author Jaroslav Fikar
 * 
*/

#pragma once
#include "CWindowManager.h"

class CSettingsManager : public CWindowManager
{
public:
    /**
    * Constructor.
    * @param interface Interface to be used.
    */
    explicit CSettingsManager(CSDLInterface *interface);

    virtual ~CSettingsManager() = default;
    CSettingsManager(const CSettingsManager &other) = delete;
    CSettingsManager &operator=(const CSettingsManager &other) = delete;

    virtual EApplicationStatus Run() override ;

    virtual void Init() override
    {}

protected:
    virtual void Draw() const override ;

    virtual void ProcessEvent(SDL_Event & e) override ;

    void UpdateResolution(CCoord <unsigned int>newResolution)
    {
        // Change settings object and reload interface.
        this->m_Interface->GetSettings()->ChangeGameScreenResolution(newResolution);
        this->m_Interface->ReloadSettings();
    }
};

