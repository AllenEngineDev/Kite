#pragma once
#include <SDL2/SDL.h>
#include "Entities/Entity.h"
#include "Components/TransformComponent.h"
#include "Components/SpriteComponent.h"
#include "Engine.h"
#include <memory>

class Player : public Entity
{
public:
    Player(SDL_Renderer* renderer); 
    void SetPosition(Vector2<int> position);
    Vector2<int> GetPosition() const { return m_Transform->GetPosition(); }
private:
    std::shared_ptr<TransformComponent> m_Transform;
    std::shared_ptr<SpriteComponent> m_Sprite;
};