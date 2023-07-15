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
}

void GameLayer::OnUpdate() 
{
    
}

void GameLayer::OnEvent(const Event& event) 
{
    std::cout << event << std::endl;
    if (event.GetType() == EventType::KeyDownEvent)
    {
        auto keyEvent = EventManager::CastEventToType<KeyDownEvent>(&event);
        game.OnKeyDown(*keyEvent);

    }
    else if (event.GetType() == EventType::MousePressedEvent)
    {
        auto mouseEvent = EventManager::CastEventToType<MousePressedEvent>(&event);
        game.OnMousePressed(*mouseEvent);
    }

}


void GameLayer::OnRender()
{
    game.RenderAllEntities();
}

