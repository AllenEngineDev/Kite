#include <SDL2/SDL_scancode.h>

#include "Game/Game.h"
#include "Components/SpriteComponent.h"
#include "Components/TransformComponent.h"

void Game::InitializeGame(SDL_Renderer* renderer)
{
    Entity* entity = new Entity;
    entity->AddComponentConstruct<TransformComponent>(
        Vector2<int>(0, 0), Vector2<int>(5, 5), 0.0f
    );

    entity->AddComponentConstruct<SpriteComponent>(renderer,
        "../res/gfx/sprites/eagle/eagle-attack-1.png");

    AddEntityToWorld(entity);
}


// TODO: Make your own Engine specific keycodes rather than using SDL Keycodes
void Game::OnKeyDown(const Event& keyEvent)
{
    std::cout << "Burger durger" << std::endl;
}

void Game::OnMousePressed(const MousePressedEvent& mouseEvent)
{
    CheckForMouseCollisions(mouseEvent.GetPressedPosition());
}

void Game::AddEntityToWorld(Entity* entity)
{
    m_Entities.emplace_back(entity);
}

void Game::RenderAllEntities(SDL_Renderer* renderer)
{
    for (Entity* entity : m_Entities)
        entity->Render(renderer);
}

void Game::CheckForMouseCollisions(Vector2<int> mousePosition)
{
    for (Entity* e : m_Entities)
    {
        if (e->IsColliding(mousePosition))
        {
            EventManager::Get().EventHappened(EntitySelectedEvent(e));
            return;
        }
    }

    // If no entity has been selected
    EventManager::Get().EventHappened(EntitySelectedEvent(nullptr));
}
 

void Game::CleanupGame()
{
    for (Entity* entity : m_Entities)
        delete entity;

    m_Entities.clear();
}

