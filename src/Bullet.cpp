#include "../Headers/Bullet.h"

Bullet::Bullet(GameObject& associated, float angle, float speed, int damage, float maxDistance, std::string sprite)
    : Component(associated), distanceLeft(maxDistance), damage(damage){
    CalculateSpeed(angle, speed);

    Sprite* bullet_sprite = new Sprite(sprite, associated); 
    associated.AddComponent((std::shared_ptr<Sprite>)bullet_sprite);
    
}

void Bullet::Render() {}

void Bullet::Update(float dt) {

    Vec2 movement = speed * dt;
    associated.box.SetCenter(associated.box.GetCenter() + movement);
    
    float pace = movement.Magnitude();
    this->distanceLeft -= pace;

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
    angle = angle * M_PI / 180.0;
    this->speed.x = std::cos(angle) * speed;
    this->speed.y = std::sin(angle) * speed;
}