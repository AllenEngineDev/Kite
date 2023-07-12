#pragma once

#define VECTOR_FLOAT_ZERO Vector2<float>(0.0f, 0.0f)
#define VECTOR_FLOAT_ONE Vector2<float>(1.0f, 1.0f)
#define VECTOR_INT_ZERO Vector2<int>(0, 0)
#define VECTOR_INT_ONE Vector2<int>(1, 1)


template<typename T>
struct Vector2
{
    T X, Y;

    // Default constructor for Vector2<int>
    Vector2()
        : X(0), Y(0) { }

    // Copy constructor
    Vector2(const Vector2<T>& other)
        : X(other.X), Y(other.Y) { }

    // Can now be used like Vector2<float>(0.1f, 0.5f)
    Vector2(T x, T y)
        : X(x), Y(y) { }

    // Operators
    Vector2 operator*(const Vector2<T>& other) const
    {
        return Vector2 { X * other.X, Y * other.Y };
    }

    Vector2 operator+(const Vector2<T>& other) const 
    {
        return Vector2 { X + other.X, Y + other.Y };
    }

    // For usage like Vector2<int> size = { 5, 5 }; size = size *  4
    // This makes sure Vector2s can be multiplied by scalar quantities. This scalar quantity must be of type T
    Vector2 operator*(const T& other) const
    {
        return Vector2 { X * other, Y * other };
    }
};