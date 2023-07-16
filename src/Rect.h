#pragma once
#include "Vector.h"
#include "imgui.h"

struct Rect {
    float X;
    float Y;
    float Width;
    float Height;

    Rect()
        : X(0.0f), Y(0.0f), Width(0.0f), Height(0.0f) { }

    // Calculates the rect's position and size based on top left
    // and bottom right coordinates
    Rect(const Vector2<float>& topLeft, const Vector2<float>& bottomRight)
    {
        X = topLeft.X;
        Y = topLeft.Y;
        Width = bottomRight.X - topLeft.X;
        Height = bottomRight.Y - topLeft.Y;
    }

    // Calculates the rect's position and size based on top left
    // and bottom right coordinates
    Rect(const ImVec2& topLeft, const ImVec2& bottomRight)
    {
        X = topLeft.x;
        Y = topLeft.y;
        Width = bottomRight.x - topLeft.x;
        Height = bottomRight.y - topLeft.y;
    }
};