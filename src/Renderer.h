#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "Components/SpriteComponent.h"
#include "Components/TransformComponent.h"
#include "Entities/Entity.h"

class Renderer
{
public:
    SDL_Renderer* GetSDLRenderer() { return m_Renderer; };

    void Init(SDL_Window* window);

    void Clear();
    void Submit(SDL_Texture* texture);
    void SubmitSprite(Sprite sprite);
    void SubmitEntity(Entity* entity);
    void Display();
    void CleanUp();
private:
    static SDL_Renderer* m_Renderer;
    static SDL_Texture* m_RenderedTexture;
};