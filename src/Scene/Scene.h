#pragma once
#include "Events/EventManager.h"

class Scene
{
public:
    // Initializes and adds Entities
    void InitializeScene(SDL_Renderer* renderer);

    // Event callbacks
    void OnKeyDown(const Event& event);
    void OnMousePressed(const MousePressedEvent& event);
    

    void CheckForMouseCollisions(Vector2<int> mousePosition);
    
    void AddEntityToWorld(Entity* entity);
    void RenderAllEntities(SDL_Renderer* renderer);

    const std::vector<Entity*>& GetEntities() const { return m_Entities; }

    void SetName(const std::string& name) { m_Name = name; }
    std::string GetName() const { return m_Name; }

    void CleanupScene();

private:
    std::vector<Entity*> m_Entities;
    std::string m_Name;
};