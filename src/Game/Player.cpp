#include "Player.h"

Player::Player()
{
    // Creating the sprite component
    auto spriteComponent = std::make_shared<Sprite>("../res/gfx/sprites/player/idle/player-idle-1.png");
    // Creating the transform component
    auto transformComponent = std::make_shared<TransformComponent>();

    AddComponent(transformComponent);
    AddComponent(spriteComponent);
}