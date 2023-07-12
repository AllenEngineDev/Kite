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
    Player(); 
};