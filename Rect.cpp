#include "Rect.h"

Rect::Rect(float x, float y, float w, float h) : x(x), y(y), w(w), h(h) {    
}

bool Rect::Contains(float pointX, float pointY) {
    return (pointX >= x && pointX <= (x + w)) && (pointY >= y && pointY <= (y + h));
}