#include "Entity.h"
#include "Components/SpriteComponent.h"
#include "Components/IDComponent.h"
#include "Components/TransformComponent.h"
#include "Engine.h"
#include "Rect.h"
#include "Core.h"

Entity::Entity()
{
    // This should not be in the constructor.
    // This is because a new ID Component will be added every time an entity is constructed
    // Becauses entities are constructed on scene load, enities will end up having 
    // multiple ID components
    auto idComponent = AddComponentConstruct<IDComponent>(this);
    // This is for ID components to be able to be queried for their parent entities
    idComponent->SetParent(this);

}

void Entity::AddComponent(const std::shared_ptr<Component> component)
{
    if (component != nullptr)
        m_Components.emplace_back(component);
}

void Entity::Render(SDL_Renderer* renderer, Rect cameraRect)
{
    // Getting the Sprite Component
    auto sprite = GetComponent<SpriteComponent>();
    if (sprite ==  nullptr)
        return;

    auto transform = GetComponent<TransformComponent>(); 
    if (transform == nullptr)
        return;

    // Position and size of the entity
    transform->SetCameraPosition(transform->GetPosition() - Vector2<int>(cameraRect.X, cameraRect.Y));
    Vector2<int> targetPosition = transform->GetCameraPosition();

    // Multiply the size of the texture by the scale the user wants it
    Vector2<int> targetScale = (sprite->GetSize() * transform->GetScale()) / Vector2<int>(cameraRect.Width, cameraRect.Height);
    SDL_Rect dstRect { targetPosition.X, targetPosition.Y, targetScale.X, targetScale.Y }; 
    SDL_Rect srcRect;
    
    srcRect.x = 0;
    srcRect.y = 0;
    srcRect.w = sprite->GetSize().X;
    srcRect.h = sprite->GetSize().Y;
    
    SDL_RenderCopy(renderer, sprite->GetTexture(), &srcRect, &dstRect);


    // TODO: Make user be able to check whether they want debug graphics or not
    // ----------- DEBUG GRAPHICS FOR SPRITE BOUNDING BOX -----------
    // SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    // SDL_RenderDrawRect(renderer, &dstRect);
    // SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);


}

// Returns true if the position passed in is within the bounds of the Sprite component added to this Entity
// That means this function will return false if there is not a Sprite
// TODO: Make an implementation that doesn't rely on the presence of a Sprite Component
// THIS IS FOR MOUSE BASED COLLISION IN THE EDITOR ONLY!
bool Entity::IsColliding(Vector2<int> posToCheck)
{
    auto transform = GetComponent<TransformComponent>();
    auto sprite = GetComponent<SpriteComponent>();

    ASSERT(transform != nullptr, "[ASSERTION FAILED]: TRANSFORM COMPONENT COULD NOT BE FOUND");
    ASSERT(sprite != nullptr, "[ASSERTION FAILED]: SPRITE COMPONENT COULD NOT BE FOUND");

    Rect rect;
    rect.X = transform->GetCameraPosition().X;
    rect.Y = transform->GetCameraPosition().Y;
    rect.Width = sprite->GetSize().X * transform->GetScale().X;
    rect.Height = sprite->GetSize().Y * transform->GetScale().Y;

    return rect.IsPositionInBounds(posToCheck);

}

