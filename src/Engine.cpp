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
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

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
            else if (event.type == SDL_WINDOWEVENT_RESIZED)
            {
                int newWidth = event.window.data1;
                int newHeight = event.window.data2;
                glViewport(0, 0, newWidth, newHeight);
            }
        }

         // Start the Dear ImGui frame
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplSDL2_NewFrame(m_Window);
        ImGui::NewFrame();
       
        // Other entities rendering pass
        m_Renderer.Clear();
        RenderAllEntities();
        m_Renderer.Display();

         // IMGUI rendering pass
        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());


        // Swap buffers
        SDL_GL_SwapWindow(m_Window);

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
    // Setting attributes for which we want to create the window
    SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
    SDL_GL_SetAttribute(SDL_GL_STENCIL_SIZE, 8);

    SDL_GL_SetAttribute(
        SDL_GL_CONTEXT_PROFILE_MASK,
        SDL_GL_CONTEXT_PROFILE_CORE
        );
    
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_FLAGS, 0); 
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 2);

    SDL_WindowFlags windowFlags = (SDL_WindowFlags)(
        SDL_WINDOW_OPENGL
        | SDL_WINDOW_RESIZABLE
        | SDL_WINDOW_ALLOW_HIGHDPI
        );

    m_Window = SDL_CreateWindow(title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 
        width, height, windowFlags);

    // Limit to which minimum size user can resize the window
    SDL_SetWindowMinimumSize(m_Window, 500, 300);

    m_Context = SDL_GL_CreateContext(m_Window);

    if (m_Context == NULL)
    {
        const char* problem = SDL_GetError();
        int a = 3;
    }

    SDL_GL_MakeCurrent(m_Window, m_Context);

    // Enable VSync
    SDL_GL_SetSwapInterval(1);
    glViewport(0, 0, width, height);

    GLenum err = glewInit();
    if (GLEW_OK != err)
    {
        // Problem: glewInit failed, something is seriously wrong. 
        auto string =  glewGetErrorString(err);
        int b = 4;
    }

    ASSERT(m_Window != NULL); 
    ASSERT(m_Context != NULL); 
    ASSERT(err == GLEW_OK);

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
    ImGui_ImplOpenGL3_Init("#version 130");
}

// Cleans up all resources. Usually called after Engine::Run()
void Engine::CleanUp()
{
    SDL_DestroyWindow(m_Window);
    m_Renderer.CleanUp();
    SDL_Quit();

    // ImGUI Cleanup
    // Cleanup
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplSDL2_Shutdown();
    ImGui::DestroyContext();

}
