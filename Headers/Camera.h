#ifndef Camera_H
#define Camera_H

#include "GameObject.h"

class Camera{
    public:
    
    static void Unfollow ();
    static void Update (float dt);
    static void Follow (GameObject* newFocus);

    static Vec2 pos;
    static Vec2 speed;

    private:
    static GameObject* focus;
};

#endif