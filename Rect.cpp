#include "Rect.h"

Rect::Rect(float x, float y, float w, float h) : x(x), y(y), w(w), h(h) {    
}

bool Rect::Contains(const Vec2& point) const {
    return (point.x >= x && point.x <= x + w && point.y >= y && point.y <= y + h);
}
