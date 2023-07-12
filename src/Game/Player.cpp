#include "Player.h"

Player::Player()
{
    // Creating the sprite component
    m_Sprite = std::make_shared<Sprite>("../res/gfx/sprites/player/idle/player-idle-1.png");
    // Creating the transform component
    m_Transform = std::make_shared<TransformComponent>();

    AddComponent(m_Transform);
    AddComponent(m_Sprite);

    GetComponent<TransformComponent>()->SetScale(Vector2<int>(5, 5));
}

void Player::SetPosition(Vector2<int> position)
{
    m_Transform->SetPosition(position);
}