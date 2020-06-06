/**
 * @author Jaroslav Fikar
 * 
*/


#include "CMenuManager.h"

EApplicationStatus CMenuManager::Run()
{
    // Did user close this window?
    while(!this->IsClosed())
    {
        CWindowManager::Run();

    }

    return EApplicationStatus ::APPLICATION_STATUS_EXIT;
}
/*====================================================================================================================*/
void CMenuManager::Update(int deltaTime)
{

}
/*====================================================================================================================*/
void CMenuManager::UpdateEvents()
{

}
/*====================================================================================================================*/
void CMenuManager::Draw() const
{

}
