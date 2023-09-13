#ifndef Component_H
#define Component_H

#include <SDL.h>
#include "GameObject.h"
#include <string>


class Component{
    public:
    Component(GameObject associated);
        float x, y;
    private:

};

#endif