/**
 * @author Jaroslav Fikar
 * 
*/


#include "CSettingsManager.h"

CSettingsManager::CSettingsManager(CSDLInterface *interface) : CWindowManager(interface)
{
    this->m_Interface->SetMenuScreenSize();


}

EApplicationStatus CSettingsManager::Run()
{
    // While window is not closed.
    while (CWindowManager::Run() != EApplicationStatus::APPLICATION_STATUS_EXIT)
    {
        if (this->m_NextApplicationState != EApplicationStatus::APPLICATON_STATUS_NONE)
        { return this->m_NextApplicationState; }
    }

    return EApplicationStatus::APPLICATION_STATUS_EXIT;
}

void CSettingsManager::Update(int deltaTime)
{

}

void CSettingsManager::UpdateEvents()
{

}

void CSettingsManager::Draw() const
{

}

