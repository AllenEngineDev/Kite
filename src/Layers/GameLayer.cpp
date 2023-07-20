#include "GameLayer.h"

#include <functional>

// Called when the ImGUI Layer is attached to the Engine Layer Stack
// Contains initialization code as well as setting up EventCallbacks
void GameLayer::OnAttach()
{   
    game.InitializeGame(m_Renderer);
    // Initializing SDL2
    int sdlInit = SDL_Init(SDL_INIT_VIDEO);
    if (sdlInit != 0)
        std::cout << "SDL Init failed! " << SDL_GetError() << std::endl;

    // Initializing SDL2_image and error checking
    int imgInit = IMG_Init(IMG_INIT_PNG);
    if (!imgInit)
        std::cout << "imgInit failed! " << SDL_GetError() << std::endl;

    // Setting up Event Callbacks
    EventManager::Get().AddCallback(EventType::KeyDownEvent,  
        std::bind(&GameLayer::OnKeyDown, this, std::placeholders::_1));

    EventManager::Get().AddCallback(EventType::MousePressedEvent,  
        std::bind(&GameLayer::OnMousePressed, this, std::placeholders::_1));
}   



void GameLayer::OnUpdate() 
{
    
}

void GameLayer::OnRender(SDL_Renderer* renderer)
{
    game.RenderAllEntities(renderer);
}


// -------------- EVENT CALLBACKS ------------

// Called when key down is pressed
void GameLayer::OnKeyDown(Event& event)
{
    const KeyDownEvent& keyEvent = static_cast<const KeyDownEvent&>(event);
    game.OnKeyDown(keyEvent);
}

// Called when the mouse button is down
void GameLayer::OnMousePressed(Event& event)
{
    const MousePressedEvent& mouseEvent = static_cast<const MousePressedEvent&>(event);
    Vector2<int> pressedPosition = mouseEvent.GetPressedPosition();
    game.CheckForMouseCollisions(pressedPosition);
}


void GameLayer::OnDetach() 
{
    game.CleanupGame();
    
    EventManager::Get().RemoveCallback(EventType::KeyDownEvent,
        std::bind(&GameLayer::OnKeyDown, this, std::placeholders::_1));
    
    EventManager::Get().RemoveCallback(EventType::MousePressedEvent,
        std::bind(&GameLayer::OnMousePressed, this, std::placeholders::_1));
}
