#include "Engine.h"
#include "imgui.h"
#include "imgui_impl_sdl2.h"
#include "imgui_impl_opengl3.h"

int main(int argv, char* args[])
{
    Engine engine;
    bool initSuccess = engine.Init();
    if (!initSuccess) 
    {
        return -1;
    }

    engine.Run();
    engine.CleanUp();
    return 0;
}