#ifndef Bullet_H
#define Bullet_H

#include <string>
#include "Vec2.h"
#include "Sprite.h"
#include "Component.h"
#include "GameObject.h"


class Bullet : public Component{
    public:
        Bullet(GameObject& associated, float angle, float speed, int damage, float maxDistance, std::string sprite);

        void Render();
        void Update(float dt);
        
        int GetDamage();

        bool Is(std::string type);

    private:
        void CalculateSpeed(float angle, float speed);

        int damage;
        float distanceLeft;
        
        Vec2 speed;
};

#endif