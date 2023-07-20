#include "Core.h"
#include "Runtime.h"

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

    m_Game.InitializeGame(m_Renderer.GetSDLRenderer());

    EventManager::Get().AddCallback(EventType::KeyDownEvent,
        std::bind(&Game::OnKeyDown, m_Game, std::placeholders::_1));

    m_HasStarted = true;
}

void Runtime::Run()
{
    m_Renderer.Clear();
    m_Game.RenderAllEntities(m_Renderer.GetSDLRenderer());
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
}
