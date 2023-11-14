#include "../Headers/Vec2.h"

Vec2::Vec2(float xrec, float yrec){
    x = xrec;
    y = yrec;
}

Vec2 operator+(const Vec2 &vector1, const Vec2 &vector2){
    int x_result = vector1.x + vector2.x;
    int y_result = vector1.y + vector2.y;
    return Vec2(x_result, y_result);
}

Vec2 operator-(const Vec2& lhs, const Vec2& rhs) {
    return Vec2(lhs.x - rhs.x, lhs.y - rhs.y);
}

Vec2 Vec2::operator*(float scalar) const {
    return Vec2(x * scalar, y * scalar);
}

float Vec2::Magnitude(){
    return std::sqrt(x * x + y * y);
}

void Vec2::Normalize() {
    float magnitude = Magnitude();
    if (magnitude != 0) {
        x /= magnitude;
        y /= magnitude;
    }
}

void Vec2::Rotate(float angle) {
    float newX = x * std::cos(angle) - y * std::sin(angle);
    float newY = x * std::sin(angle) + y * std::cos(angle);
    x = newX;
    y = newY;
}

float Vec2::RotateArgAngle(){   
    // Return value in degrees
    float argDeg =  atan2(y, x) * (180 / M_PI);
    return argDeg;
}