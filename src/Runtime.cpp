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
    m_IsRunning = true;
}

void Runtime::Stop()
{
    m_Window.CleanUp();
    m_IsRunning = false;
}
