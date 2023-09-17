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

State:: State() : quitRequested(false), music("audio/stageState.ogg"), bg("img/ocean.jpg", *new GameObject()){
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
    for (std::vector<int>::size_type i = 0; i < objectArray.size(); i++){
        objectArray[i]->Render();
    }
}

bool State::QuitRequested() {
    return quitRequested;
}

void State::Input()
{
    SDL_Event event;
    int mouseX, mouseY;

    // Obtenha as coordenadas do mouse
    SDL_GetMouseState(&mouseX, &mouseY);

    // SDL_PollEvent retorna 1 se encontrar eventos, zero caso contrário
    while (SDL_PollEvent(&event))
    {

        // Se o evento for quit, setar a flag para terminação
        if (event.type == SDL_QUIT)
        {
            quitRequested = true;
        }

        // Se o evento for clique...
        if (event.type == SDL_MOUSEBUTTONDOWN)
        {

            // Percorrer de trás pra frente pra sempre clicar no objeto mais de cima
            for (int i = objectArray.size() - 1; i >= 0; --i)
            {
                // Obtem o ponteiro e casta pra Face.
                GameObject *go = (GameObject *)objectArray[i].get();
                // Nota: Desencapsular o ponteiro é algo que devemos evitar ao máximo.
                // O propósito do unique_ptr é manter apenas uma cópia daquele ponteiro,
                // ao usar get(), violamos esse princípio e estamos menos seguros.
                // Esse código, assim como a classe Face, é provisório. Futuramente, para
                // chamar funções de GameObjects, use objectArray[i]->função() direto.

                if (go->box.Contains({(float)mouseX, (float)mouseY}))
                {
                    Face *face = (Face *)go->GetComponent("Face");
                    if (nullptr != face)
                    {
                        // Aplica dano
                        face->Damage(std::rand() % 10 + 10);
                        // Sai do loop (só queremos acertar um)
                        break;
                    }
                }
            }
        }
        if (event.type == SDL_KEYDOWN)
        {
            // Se a tecla for ESC, setar a flag de quit
            if (event.key.keysym.sym == SDLK_ESCAPE)
            {
                quitRequested = true;
            }
            // Se não, crie um objeto
            else
            {
                Vec2 objPos = Vec2(200, 0).GetRotated((-M_PI + M_PI * (rand() % 1001) / 500.0)) + Vec2(mouseX, mouseY);
                AddObject((int)objPos.x, (int)objPos.y);
            }
        }
    }
}

void State::AddObject(int mouseX, int mouseY) {
    GameObject *object = new GameObject();
	object->box.x = mouseX;
    object->box.y = mouseY;

    Sprite *sprite = new Sprite("img/penguinface.png", *object);
	object->box.w = sprite->GetWidth();
    object->box.h = sprite->GetHeight();
    
	Sound *sound = new Sound(*object, "audio/boom.wav");
	Face *face = new Face(*object);

	object->AddComponent(sprite);
    object->AddComponent(sound);
    object->AddComponent(face);
    objectArray.emplace_back(object);
}