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

protected:

    virtual void Update(int deltaTime) override ;

    virtual void UpdateEvents() override ;

    virtual void Draw() const override ;
};

