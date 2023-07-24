#include "Core.h"
#include "Renderer.h"

SDL_Texture* Renderer::m_RenderTexture;

// Initializes the renderer. Must be called before any other Renderer functions
bool Renderer::Init(SDL_Window* window)
{
    m_Renderer = SDL_CreateRenderer(window, -1, 
        SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

    if (m_Renderer != nullptr)
    {
        m_RenderTexture = SDL_CreateTexture(m_Renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, 
            1920, 1080);
        if (m_RenderTexture == nullptr)
            return false;

        return true;
    }
    else 
    {
        return false;
    }


    
}


void Renderer::Clear()
{
    SDL_RenderClear(m_Renderer);
}

void Renderer::SetTextureAsTarget()
{
    // Clearing the texture before resetting it
    SDL_DestroyTexture(m_RenderTexture);
    m_RenderTexture = SDL_CreateTexture(m_Renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, 
            1920, 1080);

    
    SDL_SetRenderTarget(m_Renderer, m_RenderTexture);
}


void Renderer::SetWindowAsTarget()
{   
    SDL_SetRenderTarget(m_Renderer, NULL);
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

void Renderer::SubmitSprite(SpriteComponent sprite)
{
    SDL_Rect dstRect { 300, 300, sprite.GetSize().X, sprite.GetSize().Y }; 
    SDL_Rect srcRect;
    
    srcRect.x = 0;
    srcRect.y = 0;
    srcRect.w = sprite.GetSize().X;
    srcRect.h = sprite.GetSize().Y;

    SDL_RenderCopy(m_Renderer, sprite.GetTexture(), &srcRect, &dstRect);
}

// To render an entity, it must have atleast a TransformComponent and a SpriteComponent
// DEPRECATED: DOES NOT WORK
// TODO: Instead of entities handling the rendering, it would be smarter to have the Renderer handle the rendering for the entities
void Renderer::SubmitEntity(Entity* entity)
{
    // entity->Render(m_Renderer);
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


