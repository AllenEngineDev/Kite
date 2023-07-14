#include "Engine.h"
#include "Entities/Entity.h"
#include "Game/Game.h"
#include "Components/TransformComponent.h"
#include "Events/EventManager.h"
#include "Layers/GameLayer.h"
#include "Layers/ImGuiLayer.h"

#include <memory>
#include <iostream>

SDL_Window* Engine::m_Window;
Renderer Engine::m_Renderer;
std::vector<Entity*> Engine::m_Entities;


// Initializes SDL and SDL_image as well as initializes the window and the Renderer
bool Engine::Init()
{
    InitWindow("Kite Engine", 800, 600);
    InitRenderer();

    GameLayer* gameLayer = new GameLayer;
    m_LayerStack.AttachLayer(gameLayer);

    m_GuiLayer = new ImGuiLayer(m_Window, m_Renderer.GetSDLRenderer());
    m_LayerStack.AttachLayer(m_GuiLayer);

    //InitImGui();
    
    m_Running = true;

    return true;
}

// Main Loop
void Engine::Run()
{
    while (m_Running)
    {
        SDL_Event event;
        while (SDL_PollEvent(&event))
        {
            ImGui_ImplSDL2_ProcessEvent(&event);
            if (event.type == SDL_QUIT)
            {
               m_Running = false; 
               break;
            }
            else if (event.type == SDL_KEYDOWN)
            {
                KeyDownEvent keyEvent(&event.key);
                m_LayerStack.OnEventLayers(keyEvent);
            }
        }


        m_GuiLayer->StartNewFrame();
        m_GuiLayer->SetupGui();

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


void Engine::AddEntityToWorld(Entity* entity)
{
    m_Entities.emplace_back(entity);
}

void Engine::RenderAllEntities()
{
    for (Entity* entity : m_Entities)
        entity->Render();
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

    if (m_Window == NULL)
        std::cout << "Failed to initialize window " << SDL_GetError() << std::endl; 
}


// Initializes SDL Renderer. The renderer can be accessed publicly using Engine::GetRenderer()
void Engine::InitRenderer()
{   
    m_Renderer.Init(m_Window);
}


// Cleans up all resources. Usually called after Engine::Run()
void Engine::CleanUp()
{

    SDL_DestroyWindow(m_Window);
    m_Renderer.CleanUp();
    SDL_Quit();

    m_LayerStack.DetachAllLayers();
}
