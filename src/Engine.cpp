#include "Engine.h"
#include "Entities/Entity.h"
#include "Game/Game.h"
#include "Components/TransformComponent.h"
#include "Events/EventManager.h"
#include <cassert>
#include <memory>

#define ASSERT(x) assert(x)

SDL_Window* Engine::m_Window;
Renderer Engine::m_Renderer;
std::vector<Entity*> Engine::m_Entities;


// Initializes SDL and SDL_image as well as initializes the window and the Renderer
bool Engine::Init()
{
    glewInit();
    // Initializing SDL2
    int sdlInit = SDL_Init(SDL_INIT_VIDEO);
    ASSERT(sdlInit == 0);

    // Initializing SDL2_image and error checking
    int imgInit = IMG_Init(IMG_INIT_PNG);
    ASSERT(imgInit);

    InitWindow("Chicken Burger", 800, 600);
    InitRenderer();
    InitImGui();
    m_Running = true;

    return true;
}

// Main Loop
void Engine::Run()
{
    Game game;
    game.InitializeGame();

    EventFn keyDownCallback = [&game](const Event& event)
    {
        game.OnKeyDown(event);
    };
    
    EventManager::AddCallback(EventType::KeyDownEvent, keyDownCallback);

    SDL_Event event;
    while (m_Running)
    {
        while (SDL_PollEvent(&event))
        {
            if (event.type == SDL_QUIT)
            {
               m_Running = false; 
               break;
            }
            else if (event.type == SDL_KEYDOWN)
            {
                EventManager::EventHappened(KeyDownEvent(&event.key));
            }
        }

        m_Renderer.Clear();
        RenderAllEntities();
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
        entity->Render(m_Renderer.GetSDLRenderer());
}

// Initializes SDL window. The window can be accessed publicly using Engine::GetWindow()
void Engine::InitWindow(const char* title, unsigned int width, unsigned int height)
{
    m_Window = SDL_CreateWindow(title, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 
        width, height, SDL_WINDOW_SHOWN);

    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
    m_Context = SDL_GL_CreateContext(m_Window);

    ASSERT(m_Window != NULL); 
}


// Initializes SDL Renderer. The renderer can be accessed publicly using Engine::GetRenderer()
void Engine::InitRenderer()
{   
    m_Renderer.Init(m_Window);
}

// Initializes ImGUI
void Engine::InitImGui()
{
    // Setup Dear ImGui context
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;

    // Setup Dear ImGui style
    ImGui::StyleColorsDark();

    
    // Setup Platform/Renderer bindings
    // window is the SDL_Window*
    // context is the SDL_GLContext
    ImGui_ImplSDL2_InitForOpenGL(m_Window, m_Context);
    ImGui_ImplOpenGL3_Init();
}

// Cleans up all resources. Usually called after Engine::Run()
void Engine::CleanUp()
{
    SDL_DestroyWindow(m_Window);
    m_Renderer.CleanUp();
    SDL_Quit();

    // // ImGUI Cleanup
    // // Cleanup
    // ImGui_ImplOpenGL3_Shutdown();
    // ImGui_ImplSDL2_Shutdown();
    // ImGui::DestroyContext();

}
