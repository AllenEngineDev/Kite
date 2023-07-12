#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "Renderer.h"


// TODO: Instead of making all of this static, just make it a class that can be instantiated in 
// the main function.
class Engine
{
public:
    static bool Init();
    static void Run();  
    static void CleanUp();

    static SDL_Window* GetWindow() { return m_Window; };
    static Renderer& GetRenderer() { return m_Renderer; }
    static void AddEntityToWorld(Entity* entity);
    static void RenderAllEntities();    

private:
    static std::vector<Entity*> m_Entities;
    static bool m_Running;
    static SDL_Window* m_Window;
    static Renderer m_Renderer;

    static void InitWindow(const char* title, unsigned int width, unsigned int height);
    static void InitRenderer();
};

