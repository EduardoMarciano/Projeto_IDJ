#include "../Headers/Bullet.h"

Bullet::Bullet(GameObject& associated, float angle, float speed, int damage, float maxDistance, std::string sprite) 
: Component::Component(associated),distanceLeft(maxDistance),damage(damage)
{

    Sprite* bullet_sprite = new Sprite(sprite, associated); 
    associated.AddComponent((std::shared_ptr<Sprite>)bullet_sprite);
    CalculateSpeed(angle,speed);
    associated.rotationAngle = this->speed.RotateArgAngle();
    
}

void Bullet::Render() {}

void Bullet::Update(float dt) {

    Vec2 movement = speed * dt;
    associated.box.SetCenter(associated.box.GetCenter() + movement);

    this->distanceLeft -= movement.Magnitude();

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