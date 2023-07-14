#include "Entity.h"
#include "Components/SpriteComponent.h"
#include "Components/TransformComponent.h"
#include "Engine.h"

void Entity::AddComponent(const std::shared_ptr<Component> component)
{
    if (component != nullptr)
        m_Components.emplace_back(component);
}

void Entity::Render()
{
    SDL_Renderer* renderer = Engine::GetRenderer().GetSDLRenderer();
    // Getting the Sprite Component
    auto sprite = GetComponent<Sprite>();
    if (sprite ==  nullptr)
        return;

    auto transform = GetComponent<TransformComponent>(); 
    if (transform == nullptr)
        return;

    // Position and size of the entity
    Vector2<int> targetPosition = transform->GetPosition();
    // Multiply the size of the texture by the scale the user wants it
    Vector2<int> targetScale = sprite->GetSize() * transform->GetScale();
    SDL_Rect dstRect { targetPosition.X, targetPosition.Y, targetScale.X, targetScale.Y }; 
    SDL_Rect srcRect;
    
    srcRect.x = 0;
    srcRect.y = 0;
    srcRect.w = sprite->GetSize().X;
    srcRect.h = sprite->GetSize().Y;
    
    SDL_RenderCopy(renderer, sprite->GetTexture(), &srcRect, &dstRect);
}


