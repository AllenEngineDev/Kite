#pragma once

#include "Renderer.h"
#include "Layers/LayerStack.h"
#include "Layers/ImGuiLayer.h"
#include "Rect.h"

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

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

    // Event Callbacks
    void OnGuiViewportChange(const Event& event);

private:
    bool m_Running;
    Rect m_ViewportRect;
    ImGuiLayer* m_GuiLayer;

    static std::vector<Entity*> m_Entities;
    static SDL_Window* m_Window;
    static Renderer m_Renderer;
    LayerStack m_LayerStack;

    void InitWindow(const char* title, unsigned int width, unsigned int height);
    void InitRenderer();
};

