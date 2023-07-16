#include "Game/Game.h"
#include <SDL2/SDL_scancode.h>

void Game::InitializeGame()
{
    m_Player = new Player;
        
    m_Player->GetComponent<TransformComponent>()->SetPosition(Vector2<int>(400, 300));
    AddEntityToWorld(m_Player);

    m_Player2 = new Player;
    m_Player2->GetComponent<TransformComponent>()->SetPosition(Vector2<int>(200, 300));

    AddEntityToWorld(m_Player2);
}

void Game::SetPlayerPosition(Vector2<int> newPos)
{
    m_Player->SetPosition(newPos);
}

// TODO: Make your own Engine specific keycodes rather than using SDL Keycodes
void Game::OnKeyDown(const KeyDownEvent& keyEvent)
{
    SDL_Scancode code = keyEvent.GetKeyCode();
    Vector2<int> targetVector;
    switch (code)
    {
        case SDL_SCANCODE_A:
            targetVector = Vector2<int>(-3, 0);
            break;
        case SDL_SCANCODE_D:
            targetVector = Vector2<int>(3, 0);
            break;
    }

    m_Player->SetPosition(m_Player->GetPosition() + targetVector);
}

void Game::OnMousePressed(const MousePressedEvent& mouseEvent)
{
    CheckForMouseCollisions(mouseEvent.GetPressedPosition());
}

void Game::AddEntityToWorld(Entity* entity)
{
    m_Entities.emplace_back(entity);
}

void Game::RenderAllEntities()
{
    for (Entity* entity : m_Entities)
        entity->Render();
}

void Game::CheckForMouseCollisions(Vector2<int> mousePosition)
{
    for (Entity* e : m_Entities)
    {
        if (e->IsColliding(mousePosition))
        {
            EventManager::EventHappened(EntitySelectedEvent(e));
        }
    }
}
 

Game::~Game()
{
    CleanupGame();
}

void Game::CleanupGame()
{
    for (Entity* entity : m_Entities)
        delete entity;

    m_Entities.clear();
}

