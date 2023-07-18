#pragma once
#include "GUIWindow.h"
#include "Rect.h"

class MainViewportGUI : public GUIWindow
{
public:
    MainViewportGUI()
        : GUIWindow("Main Viewport") { }
    MainViewportGUI(const char* name)
        : GUIWindow(name) { }
    Rect CalculateViewportRect();
};  