#include "../Headers/Vec2.h"
#include <cmath>

Vec2::Vec2()
{
    x = 0.0;
    y = 0.0;
}

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