#include <memory>
#include <iostream>

#include "Engine.h"
#include "Core.h"
#include "Entities/Entity.h"
#include "Scene/Scene.h"
#include "Components/TransformComponent.h"
#include "Events/EventManager.h"
#include "Layers/ImGuiLayer.h"
#include "Scene/SceneSerializer.h"


const int WINDOW_WIDTH = 800;
const int WINDOW_HEIGHT = 600;

Rect Engine::m_ViewportRect;

// Initializes SDL and SDL_image as well as initializes the window and the Renderer
bool Engine::Init()
{   
    // Initializing Window
    m_Window = Window(Vector2<int>(800, 600), "Game Engine");
    m_Window.SetMinimumSize(Vector2<int>(400, 300));
    m_Window.SetWindowFlags((SDL_WindowFlags)(SDL_WINDOW_RESIZABLE | SDL_WINDOW_ALLOW_HIGHDPI | SDL_WINDOW_SHOWN));
    bool windowInit = m_Window.Init();
    ASSERT(windowInit != false, "[ASSERTION FAILED: FAILED TO INITIALIZE WINDOW]: " << SDL_GetError());

    // Initializing game runtime to a few base variables
    // This does not start the runtime. 
    m_Runtime = Runtime(Vector2<int>(800, 600), "Game Runtime", 
        (SDL_WindowFlags)(SDL_WINDOW_SHOWN | SDL_WINDOW_ALLOW_HIGHDPI | SDL_WINDOW_RESIZABLE));

    // Initialiing Renderer
    bool rendererInit = m_Renderer.Init(m_Window.GetSDLWindow());
    ASSERT(rendererInit != false, "[ASSERTION FAILED: FAILED TO INITIALIZE RENDERER]: " << SDL_GetError());

    // Adding layers
    m_GameLayer = new GameLayer(m_Renderer);
    m_GuiLayer = new ImGuiLayer(m_Window.GetSDLWindow(), m_Renderer.GetSDLRenderer());
    
    m_LayerStack.AttachLayer(m_GameLayer);
    m_LayerStack.AttachLayer(m_GuiLayer);
    
    m_Running = true;

    // Setting up event callbacks
    EventManager::Get().AddCallback(EventType::GuiViewportChange, 
        std::bind(&Engine::OnGuiViewportChange, this, std::placeholders::_1));
    
    EventManager::Get().AddCallback(EventType::PlayButtonPressedEvent,
        std::bind(&Engine::OnPlayButtonPressed, this, std::placeholders::_1));

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
            bool isEventForEngine = (SDL_GetWindowFromID(event.window.windowID) == m_Window.GetSDLWindow());

            // If event happened while the engine was in focus
            if (isEventForEngine)
            {
                if (event.window.event == SDL_WINDOWEVENT_CLOSE)
                {
                    m_Running = false;
                    break;
                }
                else 
                    HandleEvents(event); 
            }
            else
            {
                if (event.window.event == SDL_WINDOWEVENT_CLOSE)
                {
                    m_Runtime.Stop();
                    SDL_RaiseWindow(m_Window.GetSDLWindow());
                    std::cout << "Runtime stopped" << std::endl;
                    break;
                }
                else
                    m_Runtime.HandleEvents(event);
            }
        }

        if (m_Runtime.HasStarted())
            m_Runtime.Run();


        // OnUpdate - Frame Logic
        m_LayerStack.UpdateLayers();

        // ------- RENDERING ---------
        // Clearing the renderer
        m_Renderer.Clear();
        
        // Copying the render data from all the layers in the layer stack to the renderer
        m_LayerStack.RenderLayers(m_Renderer.GetSDLRenderer());

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
    // SDL_RenderSetViewport(m_Renderer.GetSDLRenderer(), &viewport);
}


void Engine::OnPlayButtonPressed(const Event& event)
{
    SceneSerializer::Get().SerializeScene(*(m_GameLayer->GetScene()), "../scenes/scene.ksn");
    
    if (m_Runtime.HasStarted())
    {
        m_Runtime.Stop();
    }

    m_Runtime.Start();
    SDL_RaiseWindow(m_Runtime.GetWindow().GetSDLWindow());

    std::cout << "Runtime started" << std::endl;
}


// This handles SDL_Events and sends out the relevant EventHappened signals
void Engine::HandleEvents(SDL_Event& event)
{
    switch (event.type)
    {
        case SDL_KEYDOWN:
        {
            EventManager::Get().EventHappened(KeyDownEvent((&event.key)));
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
            
            EventManager::Get().EventHappened(MousePressedEvent(viewportPos, realPos));
            break;
        }
        case SDL_MOUSEBUTTONUP:
        {
            // TODO: Make this a function to be DRY
            int mouseX = event.button.x;
            int mouseY = event.button.y;

            // Remapping mouse positions to viewport rect positions
            // Right now, this is as simple as simple subtraction
            auto viewportPos = Vector2<int>(mouseX - m_ViewportRect.X, mouseY - m_ViewportRect.Y); 
            auto realPos = Vector2<int>(mouseX, mouseY);

            EventManager::Get().EventHappened(MouseReleasedEvent(viewportPos, realPos));

            break;
        }
        case SDL_MOUSEMOTION:
        {
            // TODO: Make this a function to be DRY
            int mouseX = event.button.x;
            int mouseY = event.button.y;

            // Remapping mouse positions to viewport rect positions
            // Right now, this is as simple as simple subtraction
            auto viewportPos = Vector2<int>(mouseX - m_ViewportRect.X, mouseY - m_ViewportRect.Y); 
            auto realPos = Vector2<int>(mouseX, mouseY);

            EventManager::Get().EventHappened(MouseMotionEvent(viewportPos, realPos));

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
