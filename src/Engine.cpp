#include "Engine.h"
#include "Entities/Entity.h"
#include "Game/Game.h"
#include "Components/TransformComponent.h"
#include "Events/EventManager.h"
#include <memory>
#include <iostream>

SDL_Window* Engine::m_Window;
Renderer Engine::m_Renderer;
std::vector<Entity*> Engine::m_Entities;

void Engine::AttachLayer(Layer* layer)
{
    m_LayerStack.AttachLayer(layer);
}


// Initializes SDL and SDL_image as well as initializes the window and the Renderer
bool Engine::Init()
{
    // Initializing SDL2
    int sdlInit = SDL_Init(SDL_INIT_VIDEO);
    if (sdlInit != 0)
        std::cout << "SDL Init failed! " << SDL_GetError() << std::endl;

    // Initializing SDL2_image and error checking
    int imgInit = IMG_Init(IMG_INIT_PNG);
    if (!imgInit)
        std::cout << "imgInit failed! " << SDL_GetError() << std::endl;

    TestLayer* t = new TestLayer;
    AttachLayer(t);

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
                EventManager::EventHappened(keyEvent); // TODO : GET RID OF THIS AND MAKE THIS WORK THROUGH LAYERS
                m_LayerStack.OnEventLayers(keyEvent);
            }
        }

        // ImGUI new frame
        ImGui_ImplSDLRenderer2_NewFrame();
        ImGui_ImplSDL2_NewFrame();
        ImGui::NewFrame();

        ImGUISetup();

        // Frame logic goes here

        // Rendering
        ImGui::Render();
        m_Renderer.Clear();
        RenderAllEntities();
        ImGui_ImplSDLRenderer2_RenderDrawData(ImGui::GetDrawData());

        m_Renderer.Display();

    }
}


void Engine::ImGUISetup()
{
    ImGui::Begin("Transform Component!");
    float targetPosition[] = { 0.0f, 0.0f };
    ImGui::SliderFloat2("Position", targetPosition, 0.0, 800.0);
    ImGui::Button("Hello!");
    ImGui::End();
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

// Initializes ImGUI
void Engine::InitImGui()
{
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls

    // Setup Dear ImGui style
    ImGui::StyleColorsDark();
    //ImGui::StyleColorsLight();

    // Setup Platform/Renderer backends
    ImGui_ImplSDL2_InitForSDLRenderer(m_Window, m_Renderer.GetSDLRenderer());
    ImGui_ImplSDLRenderer2_Init(m_Renderer.GetSDLRenderer());

}

// Cleans up all resources. Usually called after Engine::Run()
void Engine::CleanUp()
{
    // ImGUI Cleanup
    ImGui_ImplSDLRenderer2_Shutdown();
    ImGui_ImplSDL2_Shutdown();
    ImGui::DestroyContext();

    SDL_DestroyWindow(m_Window);
    m_Renderer.CleanUp();
    SDL_Quit();

    m_LayerStack.DetachAllLayers();
}
