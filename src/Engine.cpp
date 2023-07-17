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

SDL_Window* Engine::m_Window;
Renderer Engine::m_Renderer;

// Initializes SDL and SDL_image as well as initializes the window and the Renderer
bool Engine::Init()
{
    InitWindow("Kite Engine", WINDOW_WIDTH, WINDOW_HEIGHT);
    InitRenderer();

    GameLayer* gameLayer = new GameLayer;
    m_LayerStack.AttachLayer(gameLayer);

    m_GuiLayer = new ImGuiLayer(m_Window, m_Renderer.GetSDLRenderer());
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


        m_GuiLayer->SetupGui(); // TODO: Investigate whether this has to run every frame

        // OnUpdate - Frame Logic
        m_LayerStack.UpdateLayers();

        // ------- RENDERING ---------
        // Clearing the renderer
        m_Renderer.Clear();
        
        // Rendering everything!
        m_LayerStack.RenderLayers();

        m_Renderer.Display();

    }
}



// Initializes SDL window. The window can be accessed publicly using Engine::GetWindow()
void Engine::InitWindow(const char* title, unsigned int width, unsigned int height)
{
    SDL_WindowFlags windowFlags = (SDL_WindowFlags)(
        SDL_WINDOW_OPENGL
        | SDL_WINDOW_RESIZABLE
        | SDL_WINDOW_ALLOW_HIGHDPI
        );

    m_Window = SDL_CreateWindow(title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 
        width, height, windowFlags);

    SDL_SetWindowMinimumSize(m_Window, 500, 300);

    ASSERT(m_Window != nullptr, "Failed to initialize window!" << SDL_GetError());
}


// Initializes SDL Renderer. The renderer can be accessed publicly using Engine::GetRenderer()
void Engine::InitRenderer()
{   
    m_Renderer.Init(m_Window);
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
        int viewportX = (mouseX - m_ViewportRect.X) * (WINDOW_WIDTH / m_ViewportRect.Width);
        int viewportY = (mouseY - m_ViewportRect.Y) * (WINDOW_HEIGHT / m_ViewportRect.Height);
        auto viewportPos = Vector2<int>(viewportX, viewportY);
        auto realPos = Vector2<int>(mouseX, mouseY);
        EventManager::EventHappened(MousePressedEvent(viewportPos, realPos));
        break;
    }
    }
}


// Cleans up all resources. Usually called after Engine::Run()
void Engine::CleanUp()
{
    SDL_DestroyWindow(m_Window);
    m_Renderer.CleanUp();
    SDL_Quit();
    IMG_Quit();

    m_LayerStack.DetachAllLayers();
}
