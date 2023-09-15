#include "Vec2.h"
#include <cmath>

Vec2::Vec2(float x, float y) : x(x), y(y) {

}
Vec2 Vec2::GetRotated(float angle) 
 { 
     float x2 = x * cos(angle) - y * sin(angle); 
     float y2 = y * cos(angle) + x * sin(angle); 
     return Vec2(x2, y2); 
 }

 Vec2 Vec2::operator+(const Vec2& other) {
    return Vec2(x + other.x, y + other.y);
}