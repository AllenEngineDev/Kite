#pragma once

#include "imgui.h"
#include "imgui_impl_sdl2.h"
#include "imgui_impl_sdlrenderer2.h"

#include "Renderer.h"
#include "Layers/Layer.h"
#include "Rect.h"


#include <vector>
#include <string>

struct GUIData
{
    Entity* SelectedEntity = nullptr;
    std::vector<std::string> ConsoleOutputs;
};  

// TODO: We need to split this into another class for the GameWindow
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
    void OnUpdate();
    void OnRender();
    void StartNewFrame();
    void SetupGui();

    // Event Callbacks
    void OnEntitySelected(Event& event);
    void OnMousePressed(Event& event);
private:
    SDL_Texture* m_GameTexture;
    SDL_Window* m_Window;
    SDL_Renderer* m_Renderer;
    GUIData m_GUIData;
    Rect m_ViewportRect;
};