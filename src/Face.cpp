#include "../Headers/Face.h"

Face::Face(GameObject& associated):Component(associated), hitpoints(30){

}
Face::~Face(){

}
void Face::Damage(int damage, Sound* sound) {
    hitpoints -= damage;
    
    sound->Play();
    if (hitpoints <= 0) {
        associated.RequestDelete();
    }
}
void Face::Update(float dt){

}

void Face::Render(){

}

bool Face::Is(std::string type) {
    return type == "Face";
}
