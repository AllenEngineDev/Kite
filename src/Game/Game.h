#pragma once

#include "Events/EventManager.h"

class Game
{
public:
    // Initializes and adds Entities
    void InitializeGame(SDL_Renderer* renderer);

    // Event callbacks
    void OnKeyDown(const Event& event);
    void OnMousePressed(const MousePressedEvent& event);
    
    // Called in the destructor
    void CleanupGame();

    void CheckForMouseCollisions(Vector2<int> mousePosition);

    void AddEntityToWorld(Entity* entity);
    void RenderAllEntities(SDL_Renderer* renderer);

private:
    std::vector<Entity*> m_Entities;
};