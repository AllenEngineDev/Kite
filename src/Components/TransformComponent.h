#pragma once

#include "Component.h"
#include "Vector.h"

class TransformComponent : public Component
{
public:

    // Default Constructor. Sets position to 0.0f, 0.0f and scale to 1.0f, 1,0f
    TransformComponent()
        : m_Position(VECTOR_INT_ZERO), m_Scale(VECTOR_INT_ONE), m_Rotation(0.0f) {}

    // This will be needed for rendering operation. Make sure every Entity has this component
    TransformComponent(Vector2<int> position, Vector2<int> scale, float rotation)   
        : m_Position(position), m_Scale(scale), m_Rotation(rotation){}

    Vector2<int> GetScale() const { return m_Scale; }
    Vector2<int> GetPosition() const { return m_Position; }
    float GetRotationDegrees() const { return m_Rotation; }

    void SetPosition(Vector2<int> position)
    {
        m_Position = position;
    }

    void SetRotationDegrees(float rotation)
    {
        m_Rotation = rotation;
    }

    void SetScale(Vector2<int> scale)
    {
        m_Scale = scale;
    }

private:
    Vector2<int> m_Position;
    Vector2<int> m_Scale;
    float m_Rotation;
};