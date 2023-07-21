#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "Runtime.h"
#include "Window.h"
#include "Renderer.h"

#include "Layers/LayerStack.h"
#include "Layers/GameLayer.h"
#include "Layers/ImGuiLayer.h"

#include "Rect.h"
#include "Vector.h"



class Engine
{
public:
    static Rect& GetViewportRect() { return m_ViewportRect; }

    bool Init();
    void Run();  
    void CleanUp();
    void HandleEvents(SDL_Event& event);
    
    // Event Callbacks
    void OnGuiViewportChange(const Event& event);
    void OnPlayButtonPressed(const Event& event);

private:
    Runtime m_Runtime;
    GameLayer* m_GameLayer;

    Window m_Window;
    Renderer m_Renderer;

    bool m_Running;
    static Rect m_ViewportRect;

    LayerStack m_LayerStack;
    ImGuiLayer* m_GuiLayer;
    
    void HandleEvents();
};

