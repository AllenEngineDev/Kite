#include "Game/Game.h"

void Game::InitializeGame()
{
    m_Player = new Player;
        
    m_Player->GetComponent<TransformComponent>()->SetScale(Vector2<int>(5, 5));
    Engine::AddEntityToWorld(m_Player);

    m_Player2 = new Player;
    m_Player2->GetComponent<TransformComponent>()->SetPosition(Vector2<int>(400, 300));

    Engine::AddEntityToWorld(m_Player2);
}

void Game::OnKeyDown(const Event& event)
{
    auto keyEvent = EventManager::CastEventToType<KeyDownEvent>(&event);
    if (keyEvent != nullptr)
    {
        int h = 4;
    }
}

Game::~Game()
{
    CleanupGame();
}

void Game::CleanupGame()
{
    delete m_Player;
    delete m_Player2;
}