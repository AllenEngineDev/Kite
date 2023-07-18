#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "Vector.h"

class Window
{
public:
    Window();
    Window(Vector2<int> size, const char* title);   

    bool Init();

    // Getters and Setters
    SDL_Window* GetSDLWindow() { return m_Window; }
    void SetWindowFlags(SDL_WindowFlags flags) { m_WindowFlags = flags; }
    void SetSize(Vector2<int> size) { m_Size = size; }
    void SetTitle(const char* title) { m_Title = title; }
    void SetMinimumSize(Vector2<int> minSize);  
    void CleanUp() { SDL_DestroyWindow(m_Window); }

private:
    SDL_Window* m_Window;
    SDL_WindowFlags m_WindowFlags;

    Vector2<int> m_Size;
    Vector2<int> m_MinSize;
    const char* m_Title;
};