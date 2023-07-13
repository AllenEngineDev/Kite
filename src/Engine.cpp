#include "Engine.h"
#include "Entities/Entity.h"
#include "Game/Game.h"
#include "Components/TransformComponent.h"
#include "Events/EventManager.h"
#include <cassert>
#include <memory>
#include <iostream>

#define ASSERT(x) assert(x)

SDL_Window* Engine::m_Window;
Renderer Engine::m_Renderer;
std::vector<Entity*> Engine::m_Entities;


// Initializes SDL and SDL_image as well as initializes the window and the Renderer
bool Engine::Init()
{
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
                EventManager::EventHappened(KeyDownEvent(&event.key));
            }
        }

        // ImGUI new frame
        ImGui_ImplSDLRenderer2_NewFrame();
        ImGui_ImplSDL2_NewFrame();
        ImGui::NewFrame();

        IMGUIDemoWindow();

        // Frame logic goes here

        // Rendering
        ImGui::Render();
        m_Renderer.Clear();
        RenderAllEntities();
        ImGui_ImplSDLRenderer2_RenderDrawData(ImGui::GetDrawData());

        m_Renderer.Display();

    }

}

void Engine::IMGUIDemoWindow()
{
    bool show_demo_window = false;
    bool show_another_window = false;
    if (show_demo_window) { ImGui::ShowDemoWindow(&show_demo_window); }

    // a window is defined by Begin/End pair
    {
        static int counter = 0;

        int sdl_width = 0, sdl_height = 0, controls_width = 0;
        // get the window size as a base for calculating widgets geometry
        SDL_GetWindowSize(m_Window, &sdl_width, &sdl_height);
        controls_width = sdl_width;
        // make controls widget width to be 1/3 of the main window width
        if ((controls_width /= 3) < 300) { controls_width = 300; }

        // position the controls widget in the top-right corner with some margin
        ImGui::SetNextWindowPos(ImVec2(10, 10), ImGuiCond_Always);
        // here we set the calculated width and also make the height to be
        // be the height of the main window also with some margin
        ImGui::SetNextWindowSize(
            ImVec2(static_cast<float>(controls_width), static_cast<float>(sdl_height - 20)),
            ImGuiCond_Always
            );
        // create a window and append into it
        ImGui::Begin("Controls", NULL, ImGuiWindowFlags_NoResize);

        ImGui::Dummy(ImVec2(0.0f, 1.0f));
        ImGui::TextColored(ImVec4(1.0f, 0.0f, 1.0f, 1.0f), "Time");

        ImGui::Dummy(ImVec2(0.0f, 3.0f));
        ImGui::TextColored(ImVec4(1.0f, 0.0f, 1.0f, 1.0f), "Platform");
        ImGui::Text("%s", SDL_GetPlatform());
        ImGui::Text("CPU cores: %d", SDL_GetCPUCount());
        ImGui::Text("RAM: %.2f GB", SDL_GetSystemRAM() / 1024.0f);

        ImGui::Dummy(ImVec2(0.0f, 3.0f));
        ImGui::TextColored(ImVec4(1.0f, 0.0f, 1.0f, 1.0f), "Application");
        ImGui::Text("Main window width: %d", sdl_width);
        ImGui::Text("Main window height: %d", sdl_height);

        ImGui::Dummy(ImVec2(0.0f, 3.0f));
        ImGui::TextColored(ImVec4(1.0f, 0.0f, 1.0f, 1.0f), "SDL");
        // ImGui::Text("%s", compiledVal.str().c_str());
        // ImGui::Text("%s", linkedVal.str().c_str());

        ImGui::Dummy(ImVec2(0.0f, 10.0f));
        ImGui::Separator();
        ImGui::Dummy(ImVec2(0.0f, 10.0f));
        
        // buttons and most other widgets return true when clicked/edited/activated
        if (ImGui::Button("Counter button"))
        {
            std::cout << "counter button clicked\n";
            counter++;
            if (counter == 9) { ImGui::OpenPopup("Easter egg"); }
        }
        ImGui::SameLine();
        ImGui::Text("counter = %d", counter);

        if (ImGui::BeginPopupModal("Easter egg", NULL))
        {
            ImGui::Text("Ho-ho, you found me!");
            if (ImGui::Button("Buy Ultimate Orb")) { ImGui::CloseCurrentPopup(); }
            ImGui::EndPopup();
        }

        ImGui::Dummy(ImVec2(0.0f, 15.0f));
        if (!show_demo_window)
        {
            if (ImGui::Button("Open standard demo"))
            {
                show_demo_window = true;
            }
        }

        ImGui::Checkbox("show a custom window", &show_another_window);
        if (show_another_window)
        {
            ImGui::SetNextWindowSize(
                ImVec2(400.0f, 350.0f),
                ImGuiCond_FirstUseEver // after first launch it will use values from imgui.ini
                );
            // the window will have a closing button that will clear the bool variable
            ImGui::Begin("A custom window", &show_another_window);
            
            ImGui::Dummy(ImVec2(0.0f, 1.0f));
            ImGui::TextColored(ImVec4(1.0f, 0.0f, 1.0f, 1.0f), "Files in the current folder");
                            
            ImGui::Dummy(ImVec2(0.0f, 0.5f));


            ImGui::Dummy(ImVec2(0.0f, 1.0f));
            if (ImGui::Button("Close"))
            {
                std::cout << "close button clicked\n";
                show_another_window = false;
            }

            ImGui::End();
        }

        ImGui::End();
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
    SDL_WindowFlags windowFlags = (SDL_WindowFlags)(
        SDL_WINDOW_OPENGL
        | SDL_WINDOW_RESIZABLE
        | SDL_WINDOW_ALLOW_HIGHDPI
        );

    m_Window = SDL_CreateWindow(title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 
        width, height, windowFlags);

    SDL_SetWindowMinimumSize(m_Window, 500, 300);

    ASSERT(m_Window != NULL); 
    ASSERT(m_Context != NULL); 

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
    // Cleanup
    
    ImGui_ImplSDLRenderer2_Shutdown();
    ImGui_ImplSDL2_Shutdown();
    ImGui::DestroyContext();

    SDL_DestroyWindow(m_Window);
    m_Renderer.CleanUp();
    SDL_Quit();
}
