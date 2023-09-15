#ifndef Vec2_H
#define Vec2_H

#include <SDL.h>
#include <string>

class Vec2 {
public:
    float x, y;

    Vec2(float x = 0, float y = 0);
    Vec2 GetRotated(float radians);
    Vec2 operator+(const Vec2& other);
    
private:
};

#endif