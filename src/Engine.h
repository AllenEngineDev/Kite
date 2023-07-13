#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "imgui.h"
#include "imgui_impl_sdl2.h"
#include "imgui_impl_sdlrenderer2.h"
#include "Renderer.h"
#include "Layers/LayerStack.h"
#include "Layers/Layer.h"



class Engine
{
public:
    bool Init();
    void Run();  
    void CleanUp();
    void AttachLayer(Layer* layer);

    static SDL_Window* GetWindow() { return m_Window; };
    static Renderer& GetRenderer() { return m_Renderer; }
    static void AddEntityToWorld(Entity* entity);
    void RenderAllEntities();    
    void ImGUISetup();

private:
    bool m_Running;

    static std::vector<Entity*> m_Entities;
    static SDL_Window* m_Window;
    static Renderer m_Renderer;
    LayerStack m_LayerStack;

    void InitWindow(const char* title, unsigned int width, unsigned int height);
    void InitRenderer();
    void InitImGui();
};

