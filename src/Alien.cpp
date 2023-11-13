#include <cmath>
#include <iostream>

#include "../Headers/Minion.h"
#include "../Headers/Alien.h"
#include "../Headers/Game.h"

const float   ALIEN_WIDTH   = 146;
const float   ALIEN_HEIGHT  = 163;

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

void Rotation(GameObject* associated){
    float degress = abs(associated->rotationAngle*(180)/M_PI);
    if (degress >= 360){
        degress = 0;
    }else {
     degress = degress + 0.001;
    }
    associated->rotationAngle = -1*degress*(M_PI/180);

}

void Alien::Update(float dt) {

    Rotation(&associated);

    if (InputManager::GetInstance().MousePress(SDL_BUTTON_LEFT)) { 
        taskQueue.emplace(Action(SHOOT, InputManager::GetInstance().GetMouseX(), InputManager::GetInstance().GetMouseY()));
    }
    else if (InputManager::GetInstance().MousePress(SDL_BUTTON_RIGHT)) {
        taskQueue.emplace(Action(MOVE, InputManager::GetInstance().GetMouseX(), InputManager::GetInstance().GetMouseY()));
    }
    speed.x = 150;
    speed.y = 150;
    if (!taskQueue.empty()) {
        Action& item = taskQueue.front();

        if (item.type == SHOOT) {
            std::shared_ptr<GameObject> closestMinion;
            Vec2 target = taskQueue.front().pos;
            float closestDistance = std::numeric_limits<float>::max();

            for (auto& weakMinion : minionArray) {
                if (auto minion = weakMinion.lock()) {
                    float distance = (target - minion->box.GetCenter()).Magnitude();
                    if (distance < closestDistance) {
                        closestDistance = distance;
                        closestMinion = minion;
                    }
                }
            }
            if (closestMinion) {
                Minion* minionComponent = static_cast<Minion*>(closestMinion->GetComponent("Minion").get());
                if (minionComponent) {
                    minionComponent->Shoot(target);
                }
            }
            taskQueue.pop();
        
        }else if (item.type == MOVE) {
            Vec2 targetPosition(item.pos.x - ALIEN_WIDTH/2, item.pos.y - ALIEN_HEIGHT/2);
            Vec2 direction = (targetPosition - Vec2(associated.box.x, associated.box.y));
            
            direction.Normalize();

            float distance = (targetPosition - Vec2(associated.box.x, associated.box.y)).Magnitude();
            float moveDistance = speed.Magnitude() * dt;

            if (distance <= moveDistance) {
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
    std::weak_ptr<GameObject> weak_alien = Game::GetInstance().GetCurrentState().GetObjectPtr(&associated);

    for (int i = 0; i < 3; i++){
        GameObject *object_minion = new GameObject();
        Minion *minion = new Minion(*object_minion, weak_alien, (float) i * 360);
        object_minion->AddComponent((std::shared_ptr<Minion>)minion);
        std::weak_ptr<GameObject> weak_minion = Game::GetInstance().GetCurrentState().AddObject(object_minion);
        minionArray.push_back(weak_minion);
    }
}