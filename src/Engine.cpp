#include "Engine.h"
#include "Core.h"
#include "Entities/Entity.h"
#include "Game/Game.h"
#include "Components/TransformComponent.h"
#include "Events/EventManager.h"
#include "Layers/GameLayer.h"
#include "Layers/ImGuiLayer.h"

#include <memory>
#include <iostream>

const int WINDOW_WIDTH = 800;
const int WINDOW_HEIGHT = 600;

Renderer Engine::m_Renderer;
Rect Engine::m_ViewportRect;

// Initializes SDL and SDL_image as well as initializes the window and the Renderer
bool Engine::Init()
{
    // Initializing Window
    m_Window.SetSize(Vector2<int>(800, 600));
    m_Window.SetMinimumSize(Vector2<int>(400, 300));
    m_Window.SetTitle("Game Engine");
    m_Window.SetWindowFlags((SDL_WindowFlags)(SDL_WINDOW_RESIZABLE | SDL_WINDOW_ALLOW_HIGHDPI | SDL_WINDOW_SHOWN));
    bool windowInit = m_Window.Init();
    ASSERT(windowInit != false, "[ASSERTION FAILED: FAILED TO INITIALIZE WINDOW]: " << SDL_GetError());

    // Initialiing Renderer
    bool rendererInit = m_Renderer.Init(m_Window.GetSDLWindow());
    ASSERT(rendererInit != false, "[ASSERTION FAILED: FAILED TO INITIALIZE RENDERER]: " << SDL_GetError());

    // Adding layers
    GameLayer* gameLayer = new GameLayer;
    m_LayerStack.AttachLayer(gameLayer);

    m_GuiLayer = new ImGuiLayer(m_Window.GetSDLWindow(), m_Renderer.GetSDLRenderer());
    m_LayerStack.AttachLayer(m_GuiLayer);
    
    m_Running = true;

    // Setting up event callbacks
    EventManager::AddCallback(EventType::GuiViewportChange, 
        std::bind(&Engine::OnGuiViewportChange, this, std::placeholders::_1));

    return true;
}



// Main Loop
void Engine::Run()
{
    while (m_Running)
    {
        m_GuiLayer->StartNewFrame();

        SDL_Event event;
        while (SDL_PollEvent(&event))
        {
            ImGui_ImplSDL2_ProcessEvent(&event);
            if (event.type == SDL_QUIT)
            {
               m_Running = false; 
               break;
            } 
            else { HandleEvents(event); }
        }


        // OnUpdate - Frame Logic
        m_LayerStack.UpdateLayers();

        // ------- RENDERING ---------
        // Clearing the renderer
        m_Renderer.Clear();
        
        // Copying the render data from all the layers in the layer stack to the renderer
        m_LayerStack.RenderLayers();

        // Rendering everything!
        m_Renderer.Display();

    }
}



// ---------- EVENT CALLBACKS ---------
void Engine::OnGuiViewportChange(const Event& event)
{
    const GuiViewportChange& viewportEvent = static_cast<const GuiViewportChange&>(event);
    m_ViewportRect = viewportEvent.GetRect();
    SDL_Rect viewport;

    viewport.x = m_ViewportRect.X;
    viewport.y = m_ViewportRect.Y;
    viewport.w = m_ViewportRect.Width;
    viewport.h = m_ViewportRect.Height;
    SDL_RenderSetViewport(m_Renderer.GetSDLRenderer(), &viewport);
}

// This handles SDL_Events and sends out the relevant EventHappened signals
void Engine::HandleEvents(SDL_Event& event)
{
    switch (event.type)
    {
        case SDL_KEYDOWN:
        {
            EventManager::EventHappened(KeyDownEvent((&event.key)));
            break;
        }
        case SDL_MOUSEBUTTONDOWN:
        {
            int mouseX = event.button.x;
            int mouseY = event.button.y;

            // Remapping mouse positions to viewport rect positions
            // Right now, this is as simple as simple subtraction
            auto viewportPos = Vector2<int>(mouseX - m_ViewportRect.X, mouseY - m_ViewportRect.Y); 
            auto realPos = Vector2<int>(mouseX, mouseY);
            
            EventManager::EventHappened(MousePressedEvent(viewportPos, realPos));
            break;
        }
    }
}


// Cleans up all resources. Usually called after Engine::Run()
void Engine::CleanUp()
{
    m_Window.CleanUp();
    m_Renderer.CleanUp();
    SDL_Quit();
    IMG_Quit();

    m_LayerStack.DetachAllLayers();
}
