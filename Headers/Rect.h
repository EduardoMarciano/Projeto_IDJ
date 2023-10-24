#ifndef Rect_H
#define Rect_H

#include "Vec2.h"

class Rect {
public:
    float x, y, w, h;
    Rect();
    Rect(float x, float y);
    Rect(float x, float y, float w, float h);
    bool Contains(Vec2* points);
    void SetCenter(Vec2 box);
    Vec2 GetCenter();

private:
};

#endif