#include "Components/SpriteComponent.h"
#include <filesystem>
#include <string>

Sprite::Sprite(SDL_Renderer* renderer, const char* filepath)
{
    m_Texture = IMG_LoadTexture(renderer, filepath);

    int width = 0;
    int height = 0;
    int err = SDL_QueryTexture(m_Texture, NULL, NULL, &width, &height);

    
    m_Size.X = width;
    m_Size.Y = height;
}

// Multiplies the size of the Sprite by another Vectors
void Sprite::SetSize(Vector2<int> newSize)
{
    m_Size.X = newSize.X;
    m_Size.Y = newSize.Y;
}

// Multiplies the size of the Sprite by a scalar
void Sprite::SetSize(int scalar)
{
    m_Size.X = m_Size.X * scalar;
    m_Size.Y = m_Size.Y * scalar;
}