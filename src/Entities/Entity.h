#pragma once
#include <SDL2/SDL.h>
#include <vector>
#include <memory>

#include "Components/Component.h"


class Entity
{
public:
    virtual void Render();
    void AddComponent(const std::shared_ptr<Component> component);

    // Returns the component if found. Nullptr is returned if not found
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

private:
    std::vector<std::shared_ptr<Component>> m_Components; 
};