#include "GameLayer.h"

void GameLayer::OnAttach()
{   
    game.InitializeGame();
    // Initializing SDL2
    int sdlInit = SDL_Init(SDL_INIT_VIDEO);
    if (sdlInit != 0)
        std::cout << "SDL Init failed! " << SDL_GetError() << std::endl;

    // Initializing SDL2_image and error checking
    int imgInit = IMG_Init(IMG_INIT_PNG);
    if (!imgInit)
        std::cout << "imgInit failed! " << SDL_GetError() << std::endl;
}   


void GameLayer::OnDetach() 
{
    SDL_Quit();
}

void GameLayer::OnUpdate() 
{
    
}

void GameLayer::OnEvent(const Event& event) 
{
    std::cout << event << std::endl;
    auto keyEvent = EventManager::CastEventToType<KeyDownEvent>(&event);
    game.OnKeyDown(*keyEvent);
}


void GameLayer::OnRender()
{
    game.RenderAllEntities();
}