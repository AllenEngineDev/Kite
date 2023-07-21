#pragma once
#include "Window.h"
#include "Renderer.h"
#include "Scene/Scene.h"


class Engine;

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
    void Run();
    void Stop();
    void HandleEvents(SDL_Event event);
    bool HasStarted() { return m_HasStarted; }

private:
    Scene m_Scene;
    Window m_Window;
    Renderer m_Renderer;
    bool m_HasStarted = false;
};