#include <iostream>
#include <windows.h>

#include "Engine.h"

// TODO: This is not portable. 
// Consider using a cross-platform logging library, such as spdlog or glog.
class Console
{
public:
    Console()
    {
        AllocConsole();
        freopen_s(&m_ConsoleStream, "CONOUT$", "w", stdout);
    }

    ~Console()
    {
        fclose(m_ConsoleStream);
        FreeConsole();
    }
private:
    FILE* m_ConsoleStream;
};

int main(int argv, char* args[])
{
    // Create new console for logging purposes
    Console console;
    Engine engine;
    bool initSuccess = engine.Init();
    if (!initSuccess) 
    {
        std::cout << "Engine initialization failed!" << std::endl;
        return -1;
    }

    engine.Run();
    engine.CleanUp();

    return 0;
}

