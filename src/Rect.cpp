#include "Rect.h"

// Calculates the rect's position and size based on top left
// and bottom right coordinates
Rect::Rect(const Vector2<float>& topLeft, const Vector2<float>& bottomRight)
{
    X = topLeft.X;
    Y = topLeft.Y;
    Width = bottomRight.X - topLeft.X;
    Height = bottomRight.Y - topLeft.Y;
}


// Calculates the rect's position and size based on top left
// and bottom right coordinates
Rect::Rect(const ImVec2& topLeft, const ImVec2& bottomRight)
{
    X = topLeft.x;
    Y = topLeft.y;
    Width = bottomRight.x - topLeft.x;
    Height = bottomRight.y - topLeft.y;
}

void Rect::Recalculate(const ImVec2& topLeft, const ImVec2& bottomRight)
{
    X = topLeft.x;
    Y = topLeft.y;
    Width = bottomRight.x - topLeft.x;
    Height = bottomRight.y - topLeft.y;
}

bool Rect::IsPositionInBounds(const Vector2<int>& position) const
{
    int right = X + Width;
    int bottom = Y + Height;
    return (position.X >= X && position.X <= right && position.Y >= Y && position.Y <= bottom);
}


std::ostream& operator<<(std::ostream& os, const Rect& rect)
{
    os << "X: " << rect.X << ", Y: " << rect.Y << ", W: " 
        << rect.Width << ", H: " << rect.Height;

    return os;
}