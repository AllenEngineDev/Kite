#include "Renderer.h"

// Initializes the renderer. Must be called before any other Renderer functions
void Renderer::Init(SDL_Window* window)
{
    m_Renderer = SDL_CreateRenderer(window, -1, 0);
    // ASSERT(m_Renderer != NULL); 
}

void Renderer::Clear()
{
    SDL_RenderClear(m_Renderer);
}

void Renderer::Submit(SDL_Texture* texture)
{
    SDL_Rect srcRect;
    srcRect.x = 0;
    srcRect.y = 0;
    srcRect.w = 33;
    srcRect.h = 32;

    SDL_Rect destRect;
    destRect.x = 0;
    destRect.y = 0;
    destRect.w = 33;
    destRect.h = 32;

    SDL_RenderCopy(m_Renderer, texture, &srcRect, &destRect);
}

void Renderer::SubmitSprite(Sprite sprite)
{
    SDL_Rect dstRect { 300, 300, sprite.GetSize().X, sprite.GetSize().Y }; 
    SDL_Rect srcRect;
    
    srcRect.x = 0;
    srcRect.y = 0;
    srcRect.w = sprite.GetSize().X;
    srcRect.w = sprite.GetSize().Y;

    SDL_RenderCopy(m_Renderer, sprite.GetTexture(), &srcRect, &dstRect);
}

// To render an entity, it must have atleast a TransformComponent and a SpriteComponent
void Renderer::SubmitEntity(Entity* entity)
{
    entity->Render(m_Renderer);
}   


void Renderer::Display()
{
    SDL_RenderPresent(m_Renderer);
}

// Call at the end of the program to clean up
void Renderer::CleanUp()
{
    SDL_DestroyRenderer(m_Renderer);
}
