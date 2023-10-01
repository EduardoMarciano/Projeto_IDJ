#ifndef CameraFollower_H
#define CameraFollower_H

#include "Component.h"
class CameraFollower : public Component{
    public:
        CameraFollower(GameObject& go);
        
        void Render ();
        void Update (float dt);

        bool Is(std::string type);

    private:
};

#endif