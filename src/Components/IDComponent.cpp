#include "IDComponent.h"

std::random_device IDComponent::rd;
std::mt19937_64 IDComponent::generator(IDComponent::rd());
std::uniform_int_distribution<uint64_t> IDComponent::distribution;

IDComponent::IDComponent(Entity* e)
    : m_ID(distribution(generator))
{
    IDManager::Get().AddEntityToIDMap(m_ID, e);
}

void IDComponent::Serialize(YAML::Emitter& out) const 
{
    out << YAML::BeginMap; 

    out << YAML::Key << "Key1";
    out << YAML::Value << "Key value";

    out << YAML::EndMap;
}