#include "Game/Game.h"

void Game::InitializeGame()
{
    m_Player = new Player;
        
    m_Player->GetComponent<TransformComponent>()->SetPosition(Vector2<int>(400, 300));
    Engine::AddEntityToWorld(m_Player);

    m_Player2 = new Player;
    m_Player2->GetComponent<TransformComponent>()->SetPosition(Vector2<int>(200, 300));

    Engine::AddEntityToWorld(m_Player2);
}

// TODO: Make your own Engine specific keycodes rather than using SDL Keycodes
void Game::OnKeyDown(const Event& event)
{
    auto keyEvent = EventManager::CastEventToType<KeyDownEvent>(&event);
    if (keyEvent != nullptr)
    {
        int h = 4;
        SDL_Scancode code = keyEvent->GetKeyCode();
        Vector2<int> targetVector;
        switch (code)
        {
            case SDL_SCANCODE_A:
                targetVector = Vector2<int>(-3, 0);
                break;
            case SDL_SCANCODE_D:
                targetVector = Vector2<int>(3, 0);
                break;
        }

        m_Player->SetPosition(m_Player->GetPosition() + targetVector);
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