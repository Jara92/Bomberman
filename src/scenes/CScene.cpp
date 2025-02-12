/**
 * @author Jaroslav Fikar
*/

#include "CScene.h"

EApplicationStatus CScene::Run()
{
    // Tick event to update game clock
    this->m_Clock.Tick();

    // Check keyboard, mouse and program events.
    this->UpdateEvents();

    // Update manager
    this->Update(this->m_Clock.DeltaTime());

    // Draw manager output
    this->Draw();

    // Wait for few miliseconds to draw cca 60 frames per second
    this->m_Interface.Wait(this->m_Clock.GetDelay());

    return this->m_NextApplicationState;
}

/*====================================================================================================================*/
void CScene::UpdateEvents()
{
    // Proccess event.
    SDL_Event e;
    while (SDL_PollEvent(&e) != 0)
    { this->ProcessEvent(e); }
}

/*====================================================================================================================*/
void CScene::ProcessEvent(SDL_Event &e)
{
    // Check events
    switch (e.type)
    {
        case SDL_QUIT:
            this->m_NextApplicationState = EApplicationStatus::APPLICATION_STATUS_EXIT;
        default:
            return;
    }
}

/*====================================================================================================================*/
void CScene::Draw() const
{
    // Draw every UI item.
    for (auto item = this->m_InterfaceItems.begin(); item != this->m_InterfaceItems.end(); item++)
    { item->get()->Draw(this->m_Interface); }
}

/*====================================================================================================================*/
void CScene::Update(int deltaTime)
{
    for (auto item = this->m_InterfaceItems.begin(); item != this->m_InterfaceItems.end(); item++)
    { item->get()->Update(this->m_Interface, deltaTime); }
}
