#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "Vector.h"
#include "Component.h"

struct SpriteData
{
    const char* filepath;
};

class SpriteComponent : public Component
{
public:
    SpriteComponent(SDL_Renderer* renderer, const char* filepath);

    SDL_Texture* GetTexture() const { return m_Texture; }
    Vector2<int> GetSize() const { return m_Size; }
    void SetSize(Vector2<int> newSize);
    // Scalar
    void SetSize(int newSize);
    
    SpriteData GetData() { return SpriteData { m_Filepath }; }
    void Serialize(YAML::Emitter& out) const override;

    COMPONENT_NAME("SpriteComponent")
private:
    SDL_Texture* m_Texture;
    // Stores the X and Y size of the texture
    Vector2<int> m_Size;
    const char* m_Filepath;
};