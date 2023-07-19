#pragma once
#include "Window.h"
#include "Renderer.h"

class Runtime
{
public:
    Runtime() { }
    // Use this to initialize runtime to a few base variables
    // This does not start the runtime. Use runtime.Start() and runtime.Stop() for that
    Runtime(Vector2<int> windowSize, const char* windowName, SDL_WindowFlags flags);

    Window& GetWindow() { return m_Window; }
    Renderer& GetRenderer() { return m_Renderer; }

    void Start();
    void Stop();
    bool IsRunning() { return m_IsRunning; }

private:
    Window m_Window;
    Renderer m_Renderer; 
    bool m_IsRunning = false;
};