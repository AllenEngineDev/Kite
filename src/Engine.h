#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "Window.h"
#include "Renderer.h"
#include "Layers/LayerStack.h"
#include "Layers/ImGuiLayer.h"
#include "Rect.h"
#include "Vector.h"

class Engine
{
public:
    static Renderer& GetRenderer() { return m_Renderer; }
    static void AddEntityToWorld(Entity* entity);

    bool Init();
    void Run();  
    void CleanUp();
    void HandleEvents(SDL_Event& event);
    
    
    // Event Callbacks
    void OnGuiViewportChange(const Event& event);

private:
    Window m_Window;
    static Renderer m_Renderer;

    bool m_Running;
    Rect m_ViewportRect;

    LayerStack m_LayerStack;
    ImGuiLayer* m_GuiLayer;
    
    void HandleEvents();
};

