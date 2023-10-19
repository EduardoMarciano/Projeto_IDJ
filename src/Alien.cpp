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
    speed.x = 150;
    speed.y = 150;
    if (!taskQueue.empty()) {
        Action& item = taskQueue.front();

        if (item.type == SHOOT) {
            taskQueue.pop();

        } else if (item.type == MOVE) {
            Vec2 targetPosition(item.pos.x, item.pos.y);
            Vec2 direction = (targetPosition - Vec2(associated.box.x, associated.box.y));
            
            direction.Normalize();

            float distance = (targetPosition - Vec2(associated.box.x, associated.box.y)).Magnitude();
            float moveDistance = speed.Magnitude() * dt;

            if (distance <= moveDistance) {

                associated.box.x = targetPosition.x - associated.box.w / 2;
                associated.box.y = targetPosition.y - associated.box.h / 2;
                taskQueue.pop();
            } else {

                Vec2 velocity = direction * (speed.Magnitude() * dt);
                associated.box.x += velocity.x;
                associated.box.y += velocity.y;
            }
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
