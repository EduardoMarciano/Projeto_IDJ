#ifndef VEC2_H
#define VEC2_H
#include <SDL.h>
#include <string>

class Vec2 {
    public:
        float x, y;

        Vec2(float x = 0, float y = 0);
        friend Vec2 operator+(const Vec2 &, const Vec2 &);
        friend Vec2 operator-(const Vec2& lhs, const Vec2& rhs);
        Vec2 operator*(float scalar) const;

        float Magnitude();
        float RotateArgAngle();
        void Normalize();
        void Rotate(float angle);

    private:
};
#endif