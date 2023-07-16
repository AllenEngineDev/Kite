#include "Renderer.h"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"


#include <iostream>

// Initializes the renderer. Must be called before any other Renderer functions
void Renderer::Init(SDL_Window* window)
{
    m_Renderer = SDL_CreateRenderer(window, -1, 
        SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    
    if (m_Renderer == nullptr)
    {
        std::cout << "[ERROR WHEN CREATING RENDERER]: " << SDL_GetError() << std::endl;
    }
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
    entity->Render();
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


bool Renderer::LoadTextureFromFile(const char* filename, SDL_Texture** texture_ptr, int& width, int& height, SDL_Renderer* renderer) {
    int channels;
    unsigned char* data = stbi_load(filename, &width, &height, &channels, 0);

    if (data == nullptr) {
        fprintf(stderr, "Failed to load image: %s\n", stbi_failure_reason());
        return false;
    }

    SDL_Surface* surface = SDL_CreateRGBSurfaceFrom((void*)data, width, height, channels * 8, channels * width,
                                                    0x000000ff, 0x0000ff00, 0x00ff0000, 0xff000000);

    if (surface == nullptr) {
        fprintf(stderr, "Failed to create SDL surface: %s\n", SDL_GetError());
        return false;
    }

    *texture_ptr = SDL_CreateTextureFromSurface(renderer, surface);

    if ((*texture_ptr) == nullptr) {
        fprintf(stderr, "Failed to create SDL texture: %s\n", SDL_GetError());
    }

    SDL_FreeSurface(surface);
    stbi_image_free(data);

    return true;
}
