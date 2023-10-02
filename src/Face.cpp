#include "../Headers/Face.h"
#include "../Headers/Camera.h"
#include "../Headers/InputManager.h"

Face::Face(GameObject& associated):Component(associated), hitpoints(30){

}
Face::~Face(){

}
void Face::Damage(int damage) {
    hitpoints -= damage;    

    if (hitpoints <= 0) {
        associated.RequestDelete();
        Sound* sound = (Sound *)associated.GetComponent("Sound");
        sound->Play();
    }
}
void Face::Update(float dt){
    if (InputManager::GetInstance().MousePress(LEFT_MOUSE_BUTTON)){

        Vec2* vetor = new Vec2(InputManager::GetInstance().GetMouseX() - Camera::pos.x, InputManager::GetInstance().GetMouseY()- Camera::pos.y);
        
        if (associated.box.Contains(vetor)){
            int damage = std::rand() % 10 + 10;
            Damage(damage);
        }
    }

}

void Face::Render(){

}

bool Face::Is(std::string type) {
    return type == "Face";
}
