#include "../Headers/Game.h"
#include "../Headers/Sound.h"
#include "../Headers/Face.h"

State:: State() : quitRequested(false){
	GameObject *object = new GameObject();
	bg     = new Sprite("../DATA/img/ocean.jpg", *object);
	music  = new Music("../DATA/audio/stageState.ogg");
    object->AddComponent(bg);

    object->box.x = 0;
    object->box.y = 0;
    object->box.w = bg->GetWidth();
    object->box.h = bg->GetHeight();
	
	objectArray.emplace_back(object);

	music->Play(-1);
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

                if (go->box.Contains({(float)mouseX, (float)mouseY}))
                {
                    Face *face = (Face *)go->GetComponent("Face");
					Sound *sound = (Sound *)go->GetComponent("Sound");
                    if (nullptr != face){
                        face->Damage(std::rand() % 10 + 10, sound);
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

    Sprite *sprite = new Sprite("../DATA/img/penguinface.png", *object);
	object->box.w = sprite->GetWidth();
    object->box.h = sprite->GetHeight();
    
	Sound *sound = new Sound(*object, "../DATA/audio/boom.wav");
	Face *face = new Face(*object);

	object->AddComponent(sprite);
    object->AddComponent(sound);
    object->AddComponent(face);
    objectArray.emplace_back(object);
}