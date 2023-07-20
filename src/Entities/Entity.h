#pragma once
#include <SDL2/SDL.h>
#include <vector>
#include <memory>

#include "Components/Component.h"
#include "Vector.h"


class Entity
{
public:
    Entity(); // For initializing the ID component as all Entities will have this
    virtual void Render(SDL_Renderer* renderer);
    void AddComponent(const std::shared_ptr<Component> component);

    // Template function to add a component of a specified type with variadic constructor arguments
    // To be used as so entity.AddComponentConstruct<SpriteComponent>("filepath")
    // Returns a std::shared_ptr to the new component
    template<typename ComponentType, typename... Args>
    std::shared_ptr<ComponentType> AddComponentConstruct(Args&&... args)
    {
        // Create a shared pointer to the component using perfect forwarding of arguments
        std::shared_ptr<ComponentType> component = std::make_shared<ComponentType>(std::forward<Args>(args)...);

        // Add the component to the list of components
        m_Components.emplace_back(component);

        // Return the shared pointer to the added component
        return component;
    }

    // Returns the component if found. nullptr is returned if not found
    template<typename T>
    std::shared_ptr<T> GetComponent()
    {
        // Check all the components
        for (size_t i = 0; i < m_Components.size(); i++)
        {
            // Safe cast. This will return nullptr if the component doesn't match
            std::shared_ptr<T> typedComponent = std::dynamic_pointer_cast<T>(m_Components[i]); 
            if (typedComponent != nullptr)
            {
                return typedComponent;
            }
        }

        return nullptr;
    }

    bool IsColliding(Vector2<int> posToCheck);
private:
    std::vector<std::shared_ptr<Component>> m_Components; 
};