#include "Engine.h"
#include <windows.h>
#include <iostream>

int main(int argv, char* args[])
{
    // Create new console for logging purposes
    AllocConsole();
    FILE* consoleStream;
    freopen_s(&consoleStream, "CONOUT$", "w", stdout);

    Engine engine;
    bool initSuccess = engine.Init();
    if (!initSuccess) 
    {
        std::cout << "Engine initialization failed!" << std::endl;
        return -1;
    }

    engine.Run();
    engine.CleanUp();

    fclose(consoleStream);
    FreeConsole();

    return 0;
}

