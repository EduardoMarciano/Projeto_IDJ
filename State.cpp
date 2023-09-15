#include <cmath>
#include "GameObject.h"
#include "Sprite.h"
#include <iostream>
#include <SDL_image.h>
#include "Game.h"
#include "State.h"
#include "Vec2.h"
#include "Rect.h"
#include "Face.h"

State:: State(GameObject& bgObject) : quitRequested(false), music("audio/stageState.ogg"), bg(bgObject){
    bg.Open("img/ocean.jpg");
    music.Play(-1);
}

State::~State(){
    objects.clear();
}


void State::LoadAssets() {
}

void State::Update(float dt) {
    Input();
    for (int i = 0; i < objects.size(); i++) {
        objects[i]->Update(dt);
    }
    for (int i = 0; i < objects.size(); i++) {
        if (objects[i]->IsDead()) {
            objects.erase(objects.begin() + i);
            i--;
        }
    }
}

void State::Render() {
     for (const auto& object : objects) {
        object->Render();
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
			for(int i = objects.size() - 1; i >= 0; --i) {
				// Obtem o ponteiro e casta pra Face.
				GameObject* go = (GameObject*) objects[i].get();

				if(go->box.Contains( {(float)mouseX, (float)mouseY} ) ) {
					Face* face = (Face*)go->GetComponent( "Face" );
					if ( nullptr != face ) {
						// Aplica dano
						face->Damage(std::rand() % 10 + 10);
						// Sai do loop (só queremos acertar um)
						break;
					}
				}
			}
		}
		if( event.type == SDL_KEYDOWN ) {
			// Se a tecla for ESC, setar a flag de quit
			if( event.key.keysym.sym == SDLK_ESCAPE ) {
				quitRequested = true;
			}
			// Se não, crie um objeto
			else {
				Vec2 objPos = Vec2( 200, 0 ).GetRotated( -M_PI + M_PI*(rand() % 1001)/500.0 ) + Vec2( mouseX, mouseY );
				AddObject((int)objPos.x, (int)objPos.y);
			}
		}
	}
}

void State::AddObject(int mouseX, int mouseY) {
    GameObject go;
    go.AddComponent(new Sprite(go, "img/penguinface.png"));
    
    // Ajuste a posição para centralizar a imagem na posição do mouse
    int imgWidth = go.GetComponent("Sprite")->GetWidth();
    int imgHeight = go.GetComponent("Sprite")->GetHeight();
    go.box.x = mouseX - imgWidth / 2;
    go.box.y = mouseY - imgHeight / 2;
    
    go.AddComponent(new Sound(go));
    go.AddComponent(new Face(go));
    
    objects.emplace_back(std::make_unique<GameObject>(go));
}