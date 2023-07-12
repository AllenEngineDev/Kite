#pragma once
#include "Entities/Player.h"
#include "Engine.h"
#include "Events/EventManager.h"

class Game
{
public:
    ~Game();

    // Initializes and adds Entities
    void InitializeGame();

    // Event callbacks
    void OnKeyDown(const Event& event);
    
    // Called in the destructor
    void CleanupGame();
private:
    Player* m_Player;
    Player* m_Player2;
};