#include "Window.h"

Window::Window()
    : m_Size(VECTOR_INT_ZERO), m_Title("Default title")
{

}
   
Window::Window(Vector2<int> size, const char* title)
    : m_Size(size), m_Title(title)
{

}

bool Window::Init()
{
    m_Window = SDL_CreateWindow(m_Title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 
        m_Size.X, m_Size.Y, m_WindowFlags);

    return m_Window != nullptr;
}

void Window::SetMinimumSize(Vector2<int> minSize)
{
    m_MinSize = minSize;
    SDL_SetWindowMinimumSize(m_Window, m_Size.X, m_Size.Y);
}