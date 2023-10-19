#include "../Headers/Vec2.h"
#include <cmath>

Vec2::Vec2(float xrec, float yrec)
{
    x = xrec;
    y = yrec;
}

Vec2 Vec2::GetRotated(float angle)
{
    int x_rot = x * cos(angle) - y * sin(angle);
    int y_rot = y * cos(angle) + x * sin(angle);

    return Vec2(x_rot, y_rot);
}

Vec2 operator+(const Vec2 &vector1, const Vec2 &vector2)
{
    int x_result = vector1.x + vector2.x;
    int y_result = vector1.y + vector2.y;

    return Vec2(x_result, y_result);
}

Vec2 operator-(const Vec2& lhs, const Vec2& rhs) {
    return Vec2(lhs.x - rhs.x, lhs.y - rhs.y);
}

void Vec2::Normalize() {
    float length = Magnitude();
    if (length != 0) {
        x /= length;
        y /= length;
    }
}

float Vec2::Magnitude(){
    return std::sqrt(x * x + y * y);
}

Vec2 Vec2::operator*(float scalar) const {
    return Vec2(x * scalar, y * scalar);
}