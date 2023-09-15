#ifndef Rect_H
#define Rect_H

#include <SDL.h>
#include <string>
#include "Vec2.h"

class Rect {
public:
    float x, y, w, h;

    Rect(float x, float y);
    Rect(float x, float y, float w, float h);
    bool Contains(const Vec2& point) const;

private:
};

#endif
