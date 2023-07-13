#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "GL/glew.h"
#include <SDL_opengl.h>
#include "Renderer.h"
#include "imgui.h"
#include "imgui_impl_sdl2.h"
#include "imgui_impl_opengl3.h"

// TODO: Instead of making all of this static, just make it a class that can be instantiated in 
// the main function.
class Engine
{
public:
    bool Init();
    void Run();  
    void CleanUp();

    static SDL_Window* GetWindow() { return m_Window; };
    static Renderer& GetRenderer() { return m_Renderer; }
    SDL_GLContext m_Context;
    static void AddEntityToWorld(Entity* entity);
    void RenderAllEntities();    

private:
    static std::vector<Entity*> m_Entities;
    bool m_Running;
    static SDL_Window* m_Window;
    static Renderer m_Renderer;

    void InitWindow(const char* title, unsigned int width, unsigned int height);
    void InitRenderer();
    void InitImGui();
};

