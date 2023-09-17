#include <bits/types/FILE.h>
#include <cmath>
#include "GameObject.h"
#include "Sprite.h"
#include <iostream>
#include <SDL_image.h>
#include <string>
#include "Game.h"
#include "State.h"
#include "Sound.h"
#include "Vec2.h"
#include "Rect.h"
#include "Face.h"

State:: State(GameObject& bgObject) : quitRequested(false), music("audio/stageState.ogg"), bg(bgObject){
    std::string backGround = "img/ocean.jpg";
	bg.Open(backGround);
    music.Play(-1);
}

State::~State(){
    objectArray.clear();
}


void State::LoadAssets() {
}

void State::Update(float dt) {
    Input();
    for (int i = 0; i < objectArray.size(); i++) {
        objectArray[i]->Update(dt);
    }
    for (int i = 0; i < objectArray.size(); i++) {
        if (objectArray[i]->IsDead()) {
            objectArray.erase(objectArray.begin() + i);
        }
    }
}

void State::Render() {
     for (const auto& objectArray : objectArray) {
        objectArray->Render();
    }
}

bool State::QuitRequested() {
    return quitRequested;
}

void State::Input() {
	SDL_Event event;
	int mouseX, mouseY;

	SDL_GetMouseState(&mouseX, &mouseY);
	while (SDL_PollEvent(&event)) {

		if(event.type == SDL_QUIT) {
			quitRequested = true;
		}

		if(event.type == SDL_MOUSEBUTTONDOWN) {
			for(int i = objectArray.size() - 1; i >= 0; --i) {
				GameObject* go = (GameObject*) objectArray[i].get();

				if(go->box.Contains( (float)mouseX, (float)mouseY ) ) {
					std::unique_ptr<Component> component = go->GetComponent("Face");
					if(component){
	 					std::unique_ptr<Face> face(dynamic_cast<Face*>(component.release()));

						if(face){
							face->Damage(std::rand() % 10 + 10);
							break;

						}

					}
				}
			}
		}
		if( event.type == SDL_KEYDOWN ) {
			if( event.key.keysym.sym == SDLK_ESCAPE ) {
				quitRequested = true;
			}
			else {
				Vec2 objPos = Vec2( 200, 0 ).GetRotated( -M_PI + M_PI*(rand() % 1001)/500.0 ) + Vec2( mouseX, mouseY );
				AddObject((int)objPos.x, (int)objPos.y);
			}
		}
	}
}

void State::AddObject(int mouseX, int mouseY) {
    std::unique_ptr<GameObject> go(new GameObject());
    go->box.x = mouseX;
    go->box.y = mouseY;
	std::string facePenguin = "img/penguinface.png";
    std::unique_ptr<Sprite> sprite(new Sprite(facePenguin, *go));
    go->AddComponent(std::move(sprite));
    sprite->Open(facePenguin);

    std::unique_ptr<Sound> sound(new Sound(*go, "audio/boom.wav"));
    go->AddComponent(std::move(sound));
    sound->Play(1);

    std::unique_ptr<Face> face(new Face(*go));
    go->AddComponent(std::move(face));

    objectArray.emplace_back(std::move(go));
}