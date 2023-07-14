#pragma once

#include <unordered_map>
#include "Components/IDComponent.h"

// Singleton class. Get a reference by using IDManager::Get()
class IDManager
{
public:
    // Returns the single instance of IDManager
    static IDManager& Get()
    {
        static IDManager s_Instance;
        return s_Instance;
    }

    Entity* GetEntityFromID(uint64_t id)
    {
        return m_IDEntityMap[id];
    }

    void AddEntityToIDMap(uint64_t id, Entity* entity)
    {
        m_IDEntityMap[id] = entity;
    }

private:
    std::unordered_map<uint64_t, Entity*> m_IDEntityMap;
};