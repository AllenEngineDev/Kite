#include <functional>
#include <SDL2/SDL_scancode.h>

#include "Engine.h"
#include "GameLayer.h"
#include "Scene/SceneSerializer.h"

// Called when the ImGUI Layer is attached to the Engine Layer Stack
// Contains initialization code as well as setting up EventCallbacks
void GameLayer::OnAttach()
{   
    // m_Scene.InitializeScene(m_Renderer);
    // m_Scene.SetName("Test Scene");
    m_Scene = SceneSerializer::Get().DeserializeScene(m_Renderer, "../scenes/scene.ksn");
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

    EventManager::Get().AddCallback(EventType::MouseReleasedEvent,  
        std::bind(&GameLayer::OnMouseReleased, this, std::placeholders::_1));

    EventManager::Get().AddCallback(EventType::MouseMotionEvent,  
        std::bind(&GameLayer::OnMouseMotion, this, std::placeholders::_1));

    m_CameraRect = Rect(0, 0, 1, 1);
}   



void GameLayer::OnUpdate() 
{
    
}

void GameLayer::OnRender(SDL_Renderer* renderer)
{
    m_Scene->RenderAllEntities(renderer, m_CameraRect);
}


// -------------- EVENT CALLBACKS ------------

void GameLayer::OnKeyDown(Event& event)
{
    const KeyDownEvent& keyEvent = static_cast<const KeyDownEvent&>(event);
    m_Scene->OnKeyDown(keyEvent);
}

void GameLayer::OnMouseMotion(Event& event)
{
    const MouseMotionEvent& mouseEvent = static_cast<const MouseMotionEvent&>(event);
    if (m_IsCameraDragged)
    {
        // Calculate the mouse movement delta.
        Vector2<int> dragDelta = mouseEvent.GetMousePosition() - m_DragStartPosition;

        // Update the camera position based on the mouse movement delta.
        m_CameraRect.X = m_CameraRect.X - (dragDelta.X * 0.5);
        m_CameraRect.Y = m_CameraRect.Y - (dragDelta.Y * 0.5);

        // Update the initial mouse position for the next frame.
        m_DragStartPosition = mouseEvent.GetMousePosition();
    }
}

void GameLayer::OnMousePressed(Event& event)
{
    const MousePressedEvent& mouseEvent = static_cast<const MousePressedEvent&>(event);

    m_IsCameraDragged = true;

    Vector2<int> pressedPosition = mouseEvent.GetPressedPosition();
    m_DragStartPosition = pressedPosition;
    m_Scene->CheckForMouseCollisions(pressedPosition);
}

void GameLayer::OnMouseReleased(Event& event)
{
    const MouseReleasedEvent& mouseEvent = static_cast<const MouseReleasedEvent&>(event);

    m_IsCameraDragged = false;
    Vector2<int> pressedPosition = mouseEvent.GetPressedPosition();
}


void GameLayer::OnDetach() 
{
    m_Scene->CleanupScene();
    
    EventManager::Get().RemoveCallback(EventType::KeyDownEvent,
        std::bind(&GameLayer::OnKeyDown, this, std::placeholders::_1));
    
    EventManager::Get().RemoveCallback(EventType::MousePressedEvent,
        std::bind(&GameLayer::OnMousePressed, this, std::placeholders::_1));

    EventManager::Get().RemoveCallback(EventType::MouseReleasedEvent,  
        std::bind(&GameLayer::OnMouseReleased, this, std::placeholders::_1));
}
