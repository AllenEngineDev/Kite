#include "IDComponent.h"

std::random_device IDComponent::rd;
std::mt19937_64 IDComponent::generator(IDComponent::rd());
std::uniform_int_distribution<uint64_t> IDComponent::distribution;

IDComponent::IDComponent(Entity* e)
    : m_ID(distribution(generator))
{
    std::cout << "Entity with ID " << m_ID << " added to IDManager\n";
    IDManager::Get().AddEntityToIDMap(m_ID, e);
}
