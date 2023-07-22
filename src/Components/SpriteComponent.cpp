#include "Core.h"
#include "Components/SpriteComponent.h"
#include "Engine.h"
#include <filesystem>
#include <string>

SpriteComponent::SpriteComponent(SDL_Renderer* renderer, const char* filepath)
    : m_Renderer(renderer), m_Filepath(std::string(filepath)) 
{
    m_Texture = IMG_LoadTexture(renderer, filepath);

    ASSERT(m_Texture != nullptr, "[ERROR WHEN GETTING TEXTURE]: " 
            <<  SDL_GetError() << " [FILEPATH: " << filepath << " ]");

    int width = 0;
    int height = 0;
    int err = SDL_QueryTexture(m_Texture, NULL, NULL, &width, &height);

    m_Size.X = width;
    m_Size.Y = height;
}

void SpriteComponent::ChangeTexture(const char* filepath)
{
    m_Filepath = std::string(filepath);
    m_Texture = IMG_LoadTexture(m_Renderer, filepath);
    ASSERT(m_Texture != nullptr, "[ERROR WHEN GETTING TEXTURE]: " 
            <<  SDL_GetError() << " [FILEPATH: " << filepath << " ]");

    int width = 0;
    int height = 0;
    int err = SDL_QueryTexture(m_Texture, NULL, NULL, &width, &height);

    m_Size.X = width;
    m_Size.Y = height;

}

// Multiplies the size of the SpriteComponent by another Vectors
void SpriteComponent::SetSize(Vector2<int> newSize)
{
    m_Size.X = newSize.X;
    m_Size.Y = newSize.Y;
}

// Multiplies the size of the SpriteComponent by a scalar
void SpriteComponent::SetSize(int scalar)
{
    m_Size.X = m_Size.X * scalar;
    m_Size.Y = m_Size.Y * scalar;
}

void SpriteComponent::Serialize(YAML::Emitter& out) const 
{
    out << YAML::BeginMap; 

    out << YAML::Key << "Filepath";
    out << YAML::Value << m_Filepath;

    out << YAML::EndMap;
}