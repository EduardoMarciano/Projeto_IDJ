#include "../Headers/Game.h"
#include "../Headers/Bullet.h"
#include "../Headers/Sprite.h"
#include "../Headers/Minion.h"
#include <iostream>
#include <memory>
#include <cmath>

const float ANGULAR_SPEED = M_PI / 4.0f;

Minion::Minion(GameObject& associated, std::weak_ptr<GameObject> alienCenter, float arcOffsetDeg) : Component(associated), alienCenter(alienCenter), arc(arcOffsetDeg), radius(100){
    
    if (auto center = alienCenter.lock()) {
    Sprite *minionSprite = new Sprite("../DATA/img/minion.png", associated);    
    associated.AddComponent((std::shared_ptr<Sprite>) minionSprite);

    minionSprite->SetScale(1.25F, 1.25F);
    
    }else{
        associated.RequestDelete();
    }
}

void Minion::Update(float dt) {
    if (auto center = alienCenter.lock()) {
        arc += ANGULAR_SPEED * dt;
        Vec2 offset = {this->radius, 0};
        offset.Rotate(arc);
        Vec2 centerPosition = center.get()->box.GetCenter();
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
void Minion::Shoot(Vec2 target) {
    float angle = atan2(target.y - associated.box.y, target.x - associated.box.x);
    float distance = sqrt(pow(target.x - associated.box.GetCenter().x, 2) + pow(target.y - associated.box.GetCenter().y, 2));
    
    GameObject* bulletObject = new GameObject();
    bulletObject->box =associated.box;

    Bullet* bullet = new Bullet(*bulletObject, angle, 500, 10, distance, "../DATA/img/minionbullet1.png");
    bulletObject->AddComponent((std::shared_ptr<Bullet>)bullet);
    Game::GetInstance().GetCurrentState().AddObject(bulletObject);
    std::cout << "MINION SHOOT " << std::endl;
}