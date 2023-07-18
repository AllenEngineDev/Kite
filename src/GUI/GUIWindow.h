#pragma once
#include <imgui.h>

// Main class of all ImGui windows
// Implements some basic stuff like Begin() -> ImGui::Begin(...) etc
class GUIWindow
{
public:
    GUIWindow(const char* name) 
        : m_Name(name) { }
    
    void Begin() { ImGui::Begin(m_Name); }
    void End() { ImGui::End(); }
private:
    const char* m_Name;
};