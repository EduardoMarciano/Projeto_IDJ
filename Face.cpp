#include <iostream>
#include "Component.h"
#include "GameObject.h"
#include "Face.h"
#include "Sound.h"

Face::Face(GameObject& associated):Component(associated), hitpoints(30){

}

void Face::Damage(int damage) {
    hitpoints -= damage;
    if (hitpoints <= 0) {
        GameObject* owner = &associated;
        if (owner != nullptr) {
            owner->RequestDelete();
            
            Sound* sound = dynamic_cast<Sound*>(owner->GetComponent("Sound"));
            if (sound != nullptr) {
                sound->Play();
            }
        }
    }
}

void Face::Update(float dt){

}

void Face::Render(){

}

bool Face::Is(std::string type) {
    return type == "Face";
}
