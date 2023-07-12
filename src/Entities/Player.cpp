#include "Player.h"

Player::Player()
{
    // Getting the renderer because unfortunately we need this information for SDL to create the texture for 
    // the sprite
    SDL_Renderer* renderer = Engine::GetRenderer().GetSDLRenderer();

    // Creating the sprite component
    auto spriteComponent = std::make_shared<Sprite>(renderer, 
        "../res/gfx/sprites/player/idle/player-idle-1.png");
    
    // Creating the transform component
    auto transformComponent = std::make_shared<TransformComponent>();

    AddComponent(transformComponent);
    AddComponent(spriteComponent);
}