#include "Engine.h"
#include "GL/glew.h"

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