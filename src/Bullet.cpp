#include "../Headers/Bullet.h"
#include <iostream>

Bullet::Bullet(GameObject& associated, float angle, float speed, int damage, float maxDistance, std::string sprite) 
: Component::Component(associated),distanceLeft(maxDistance),damage(damage){
    associated.rotationAngle = angle;
    Sprite* bullet_sprite = new Sprite(sprite, associated); 
    associated.AddComponent((std::shared_ptr<Sprite>)bullet_sprite);
    CalculateSpeed(angle, speed);

}   

void Bullet::Render() {}

void Bullet::Update(float dt) {
    float deltaX = cos(associated.rotationAngle) * speed.Magnitude() * dt;
    float deltaY = sin(associated.rotationAngle) * speed.Magnitude() * dt;
    associated.box.x = associated.box.x + deltaX;
    associated.box.y = associated.box.y + deltaY;

    this->distanceLeft -= sqrt(deltaX * deltaX + deltaY * deltaY);
    if (this->distanceLeft <= 0) {
        this->associated.RequestDelete();
    }
}

int Bullet::GetDamage() {
    return this->damage;
}

bool Bullet::Is(std::string type) {
    return type == "Bullet";
}

void Bullet::CalculateSpeed(float angle, float speed) {   
    this->speed.x = cos(angle) * speed;
    this->speed.y = sin(angle) * speed;
}