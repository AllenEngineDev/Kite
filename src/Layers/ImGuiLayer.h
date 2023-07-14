#pragma once

#include "Layers/Layer.h"
#include <SDL2/SDL.h>
#include "imgui.h"
#include "imgui_impl_sdl2.h"
#include "imgui_impl_sdlrenderer2.h"
#include "Renderer.h"

class ImGuiLayer : public Layer
{
public:
    // This exists purely to pass in the window and the renderer from the Engine
    ImGuiLayer(SDL_Window* window, SDL_Renderer* renderer)  
        : m_Window(window), m_Renderer(renderer) { }

    LAYER_NAME(ImGuiLayer)
    // SDL, SDL_IMG, SDL Renderer, IMGUI Initialization code 
    void OnAttach();
    void OnDetach();
    void OnEvent(const Event& event);
    void OnUpdate();
    void OnRender();
    void StartNewFrame();
    void SetupGui();
private:
    SDL_Window* m_Window;
    SDL_Renderer* m_Renderer;
};