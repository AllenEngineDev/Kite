#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "Vector.h"
#include "Component.h"

class Sprite : public Component
{
public:
    Sprite(SDL_Renderer* renderer, const char* filepath);

    SDL_Texture* GetTexture() const { return m_Texture; }
    Vector2<int> GetSize() const { return m_Size; }
    void SetSize(Vector2<int> newSize);
    // Scalar
    void SetSize(int newSize);
private:
    SDL_Texture* m_Texture;
    Vector2<int> m_Size;
};