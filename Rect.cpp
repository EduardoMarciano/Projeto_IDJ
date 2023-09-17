#include "Rect.h"

Rect::Rect(){
    x = 0.0;
    y = 0.0;
    w = 0.0;
    h = 0.0;
}

Rect::Rect(float x, float y, float w, float h) : x(x), y(y), w(w), h(h) {    
}

bool Rect::Contains(Vec2 point) {
    bool isInsideWidth = point.x >= x && point.x <= (w + x);
    bool isInsideHeight = point.y >= y && point.y <= (h + y);
    return isInsideWidth && isInsideHeight;
}