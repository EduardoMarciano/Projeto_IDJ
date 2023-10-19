#include "../Headers/Sprite.h"
#include "../Headers/Minion.h"
#include <memory>
#include <cmath>

Minion::Minion(GameObject& associated, std::weak_ptr<GameObject> alienCenter, float arcOffsetDeg)
: Component(associated), alienCenter(alienCenter), arc(arcOffsetDeg){
    Sprite *minionSprite = new Sprite("../DATA/img/minion.png", associated);
    associated.AddComponent((std::shared_ptr<Sprite>) minionSprite);
}

void Minion::Update(float dt) {
    const float ANGULAR_SPEED = M_PI;

    if (std::shared_ptr<GameObject> center = alienCenter.lock()) {
        arc += ANGULAR_SPEED * dt;

        Vec2 offset = {200, 0};
        offset.Rotate(arc);

        associated.box.x = center->box.x/2 + offset.x - associated.box.w / 2;
        associated.box.y = center->box.y/2 + offset.y - associated.box.h / 2;
    } else {
        associated.RequestDelete();
    }
}

void Minion::Render(){}

bool Minion::Is(std::string type){
    return (type == "Minion");
}