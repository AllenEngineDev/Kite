#include "Player.h"

Player::Player()
{
    // Adding transform component
    m_Transform = AddComponentConstruct<TransformComponent>();

    AddComponentConstruct<SpriteComponent>("../res/gfx/sprites/eagle/eagle-attack-1.png");

    GetComponent<TransformComponent>()->SetScale(Vector2<int>(5, 5));
}

void Player::SetPosition(Vector2<int> position)
{
    m_Transform->SetPosition(position);
}