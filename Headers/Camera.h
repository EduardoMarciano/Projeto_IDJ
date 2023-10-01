#ifndef Camera_H
#define Camera_H

#include "GameObject.h"

class Camera{
    public:
    
    void Unfollow ();
    void Update (float dt);
    void Follow (GameObject* newFocus);

    Vec2 pos;
    Vec2 speed;

    private:
    GameObject* focus;
};

#endif