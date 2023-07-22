#include <SDL2/SDL_scancode.h>
#include "Scene/Scene.h"
#include "Components/SpriteComponent.h"
#include "Components/TransformComponent.h"

void Scene::InitializeScene(SDL_Renderer* renderer)
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
void Scene::OnKeyDown(const Event& keyEvent)
{
}

void Scene::OnMousePressed(const MousePressedEvent& mouseEvent)
{
    CheckForMouseCollisions(mouseEvent.GetPressedPosition());
}

void Scene::AddEntityToWorld(Entity* entity)
{
    m_Entities.emplace_back(entity);
}

void Scene::RenderAllEntities(SDL_Renderer* renderer, Rect cameraRect)
{
    for (Entity* entity : m_Entities)
        entity->Render(renderer, cameraRect);
}

void Scene::CheckForMouseCollisions(Vector2<int> mousePosition)
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
 

void Scene::CleanupScene()
{
    for (Entity* entity : m_Entities)
        delete entity;

    m_Entities.clear();
}

