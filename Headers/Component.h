#ifndef Component_H
#define Component_H

#include <SDL.h>
#include <string>
#include "GameObject.h"

class Component {
public:
    Component(GameObject& associated);
    virtual ~Component();
    

    virtual void Update(float dt)= 0;
    virtual void Render() = 0;
    virtual void Start();
    virtual bool Is(std::string type) = 0;

protected:
    GameObject& associated;
};

#endif