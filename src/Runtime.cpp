#include "Core.h"
#include "Runtime.h"
#include "Scene/SceneSerializer.h"

Runtime::Runtime(Vector2<int> windowSize, const char* windowName, SDL_WindowFlags flags)
{
    m_Window = Window(windowSize, windowName);
    m_Window.SetWindowFlags(flags);
}

void Runtime::Start()
{
    bool initSuccess = m_Window.Init();
    ASSERT(initSuccess, "[ASSERTION FAILED: FAILED TO INITIALIZE RUNTIME WINDOW]: " << SDL_GetError());

    bool rendererSuccess = m_Renderer.Init(m_Window.GetSDLWindow());
    ASSERT(rendererSuccess, "[ASSERTION FAILED: FAILED TO INITIALIZE RENDERER]: " << SDL_GetError());

    m_Scene = SceneSerializer::Get().DeserializeScene(m_Renderer.GetSDLRenderer(), "../scenes/scene.ksn");

    EventManager::Get().AddCallback(EventType::KeyDownEvent,
        std::bind(&Scene::OnKeyDown, m_Scene, std::placeholders::_1));

    m_HasStarted = true;
}

void Runtime::Run()
{
    m_Renderer.Clear();
    m_Scene->RenderAllEntities(m_Renderer.GetSDLRenderer());
    m_Renderer.Display();
}

void Runtime::HandleEvents(SDL_Event event)
{
    switch (event.type)
    {
        case SDL_KEYDOWN:
        {
            EventManager::Get().EventHappened(KeyDownEvent((&event.key)));
            break;
        }
    }
}

void Runtime::Stop()
{
    m_HasStarted = false;
    m_Window.CleanUp();
    m_Renderer.CleanUp();
    m_Scene->CleanupScene();
    delete m_Scene;
}
