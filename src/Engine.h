#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "Renderer.h"
#include "Layers/LayerStack.h"
#include "Layers/ImGuiLayer.h"


class Engine
{
public:
    bool Init();
    void Run();  
    void CleanUp();

    static SDL_Window* GetWindow() { return m_Window; };
    static Renderer& GetRenderer() { return m_Renderer; }
    static void AddEntityToWorld(Entity* entity);
    void RenderAllEntities();    
private:
    bool m_Running;

    ImGuiLayer* m_GuiLayer;

    static std::vector<Entity*> m_Entities;
    static SDL_Window* m_Window;
    static Renderer m_Renderer;
    LayerStack m_LayerStack;

    void InitWindow(const char* title, unsigned int width, unsigned int height);
    void InitRenderer();
};

