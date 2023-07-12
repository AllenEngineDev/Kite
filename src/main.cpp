#include "Engine.h"

int main(int argv, char* args[])
{
    bool initSuccess = Engine::Init();
    if (!initSuccess) 
    {
        return -1;
    }

    Engine::Run();
    Engine::CleanUp();
    return 0;
}