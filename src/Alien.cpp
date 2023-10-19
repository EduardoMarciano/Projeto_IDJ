#include "../Headers/Alien.h"

Alien::Action::Action(ActionType type, float x, float y) : type(type), pos(x, y){
}

Alien::Alien(GameObject &associated, int nMinions):Component::Component(associated), hp(50){

    Sprite *alien_sprite = new Sprite("../DATA/img/alien.png", associated);
    associated.AddComponent((std::shared_ptr<Sprite>)alien_sprite);
}

Alien::~Alien(){
    for (int i = minionArray.size() - 1; i >= 0; i--){
        minionArray.erase(minionArray.begin() + i);
    }
    minionArray.clear();
}

void Alien::Update(float dt) {
    if (InputManager::GetInstance().MousePress(SDL_BUTTON_LEFT)){ 
        taskQueue.emplace(Action(SHOOT, InputManager::GetInstance().GetMouseX(), InputManager::GetInstance().GetMouseY()));
    }
    else if (InputManager::GetInstance().MousePress(SDL_BUTTON_RIGHT)){
        taskQueue.emplace(Action(MOVE, InputManager::GetInstance().GetMouseX(), InputManager::GetInstance().GetMouseY()));
    }

    if (!taskQueue.empty()) {
        float step = dt * 150;

    Vec2 targetPosition(taskQueue.front().pos.x, taskQueue.front().pos.y);
    Vec2 currentPosition(associated.box.x + associated.box.w / 2, associated.box.y + associated.box.h / 2);

    Vec2 direction = targetPosition - currentPosition;
    float distance = direction.Magnitude();

    if (distance > step) {
        direction.Normalize();
        Vec2 velocity = direction * step;
        associated.box.x += velocity.x;
        associated.box.y += velocity.y;
    } else {
        associated.box.x = targetPosition.x - associated.box.w / 2;
        associated.box.y = targetPosition.y - associated.box.h / 2;
        taskQueue.pop();
    }
}
        
    if (hp <= 0) {
        associated.RequestDelete();
    }
}
bool Alien::Is(std::string type){
    return (type == "Alien");
}

void Alien::Render(){

}

void Alien::Start(){
    
}
