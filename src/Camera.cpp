#include "../Headers/Camera.h"
#include "../Headers/InputManager.h"

GameObject* Camera::focus;

Vec2 Camera::pos;
Vec2 Camera::speed;

void Camera::Follow(GameObject* newFocus) {
    focus = newFocus;
}

void Camera::Unfollow() {
    focus = nullptr;
}

void Camera::Update(float dt) {
    int velocidade = 200;

    if (focus == nullptr) {
        speed.x = 0;
        speed.y = 0;

        if (InputManager::GetInstance().IsKeyDown(RIGHT_ARROW_KEY)){
            speed.x = velocidade;
        }
        else if(InputManager::GetInstance().IsKeyDown(LEFT_ARROW_KEY)){
            speed.x = -1 * velocidade;
        }
        
        if (InputManager::GetInstance().IsKeyDown(UP_ARROW_KEY)){
            speed.y = -1 * velocidade;
        }
        else if(InputManager::GetInstance().IsKeyDown(DOWN_ARROW_KEY)){
            speed.y = velocidade;
        }

        pos.x += dt * speed.x;
        pos.y += dt * speed.y;
    }
}
 


