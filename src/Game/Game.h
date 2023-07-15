#pragma once

#include "Game/Player.h"
#include "Engine.h"
#include "Events/EventManager.h"
#include "Components/IDComponent.h"

class Game
{
public:
    ~Game();

    // Initializes and adds Entities
    void InitializeGame();

    // Event callbacks
    void OnKeyDown(const KeyDownEvent& event);
    void OnMousePressed(const MousePressedEvent& event);
    
    // Called in the destructor
    void CleanupGame();

    void SetPlayerPosition(Vector2<int> newPos);


    void CheckForMouseCollisions(Vector2<int> mousePosition);

    Vector2<int> GetPlayerPosition() const { return m_Player->GetPosition(); }
    void AddEntityToWorld(Entity* entity);
    void RenderAllEntities();

    
private:
    std::vector<Entity*> m_Entities;
    Player* m_Player;
    Player* m_Player2;
};