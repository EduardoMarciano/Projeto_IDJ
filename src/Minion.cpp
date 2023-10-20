#include "../Headers/Sprite.h"
#include "../Headers/Minion.h"
#include <memory>
#include <cmath>

const float ANGULAR_SPEED = M_PI / 2.0f;

Minion::Minion(GameObject& associated, std::weak_ptr<GameObject> alienCenter, float arcOffsetDeg) : Component(associated), alienCenter(alienCenter), arc(arcOffsetDeg){
    
    if (auto center = alienCenter.lock()) {
    associated.box.x = center->box.x;
    associated.box.y = center->box.y;
    associated.box.w = center->box.w;
    associated.box.h = center->box.h;
    Sprite *minionSprite = new Sprite("../DATA/img/minion.png", associated);    
    associated.AddComponent((std::shared_ptr<Sprite>) minionSprite);
    }else{
        associated.RequestDelete();
    }
}

void Minion::Update(float dt) {
    if (auto center = alienCenter.lock()) {
        arc += ANGULAR_SPEED * dt;
        Vec2 centerPosition = Vec2(center->box.x + center->box.w / 2, center->box.y + center->box.h / 2);
        Vec2 offset = {200, 0};
        offset.Rotate(arc);
        associated.box.x = centerPosition.x + offset.x - associated.box.w / 2;
        associated.box.y = centerPosition.y + offset.y - associated.box.h / 2;
    } else {
        associated.RequestDelete();
    }
}

void Minion::Render(){}

bool Minion::Is(std::string type){
    return (type == "Minion");
}