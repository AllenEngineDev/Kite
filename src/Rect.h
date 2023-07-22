#pragma once
#include <imgui.h>
#include "Vector.h"

struct Rect {
    float X;
    float Y;
    float Width;
    float Height;

    Rect(float x, float y, float width, float height)
        : X(x), Y(y), Width(width), Height(height) { }

    Rect()
        : X(0.0f), Y(0.0f), Width(0.0f), Height(0.0f) { }


    Rect(const Vector2<float>& topLeft, const Vector2<float>& bottomRight);
    Rect(const ImVec2& topLeft, const ImVec2& bottomRight);

    void Recalculate(const ImVec2& topLeft, const ImVec2& bottomRight);
    bool IsPositionInBounds(const Vector2<int>& position) const;

};

std::ostream& operator<<(std::ostream& os, const Rect& rect);