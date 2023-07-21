#pragma once
#include <string>
#include <yaml-cpp/yaml.h>

// This is to prevent cyclic dependency issues if I include "Entity.h" here because it includes components
class Entity; // Forward declaration of the Entity class

#define COMPONENT_NAME(x) std::string GetName() override { return x; }


class Component
{
public:
    Entity& GetParent() const { return *m_Parent; }
    void SetParent(Entity* entity) 
    {
        m_Parent = entity;
    }

    virtual std::string GetName()
    {
        return "Component";
    }
    
    virtual void Serialize(YAML::Emitter& out) const = 0;
private:
    Entity* m_Parent;
};