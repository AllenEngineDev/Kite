#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "Components/SpriteComponent.h"
#include "Components/TransformComponent.h"
#include "Entities/Entity.h"

class Renderer
{
public:
    bool Init(SDL_Window* window);
    void Clear();
    void Submit(SDL_Texture* texture);
    void SubmitSprite(SpriteComponent sprite);
    void SubmitEntity(Entity* entity);
    void Display();
    void SetTextureAsTarget();
    void SetWindowAsTarget();
    void CleanUp();

    SDL_Renderer* GetSDLRenderer() { return m_Renderer; };
    static SDL_Texture* GetRenderTexture() { return m_RenderTexture; }
private:
    SDL_Renderer* m_Renderer;
    static SDL_Texture* m_RenderTexture;
};