#pragma once
#include "Component.h"
#include <random>

class Entity;

class IDComponent : public Component
{
public:
    IDComponent()
        : m_ID(distribution(generator)) // Initialize m_ID using the generator and distribution
    {
    }   

    uint64_t GetID() const { return m_ID; }

private:
    static std::random_device rd;                   // Obtain a random seed from the hardware
    static std::mt19937_64 generator;
    static std::uniform_int_distribution<uint64_t> distribution;

    uint64_t m_ID;
};


// Make ID Component hashable so it can be used in std::unordered_map
// I don't really understand this code as I got it online, but it works
namespace std {
    template<>
    struct hash<IDComponent>
    {
        size_t operator()(const IDComponent& idComponent)
        {
            return hash<uint64_t>()(idComponent.GetID());
        }
    };
}
    

// Define static members outside the class
std::random_device IDComponent::rd;
std::mt19937_64 IDComponent::generator(IDComponent::rd());
std::uniform_int_distribution<uint64_t> IDComponent::distribution;