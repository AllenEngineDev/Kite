#pragma once
#include <string>

// This is to prevent cyclic dependency issues if I include "Entity.h" here because it includes components
class Entity; // Forward declaration of the Entity class


class Component
{
public:
    Entity& GetParent() const { return *m_Parent; }
    void SetParent(Entity* entity) 
    {
        m_Parent = entity;
    } 
private:
    Entity* m_Parent;
    virtual std::string GetName()
    {
        return "Component";
    }
};