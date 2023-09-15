#ifndef Sound_H
#define Sound_H

#include "Component.h"
#include "SDL_mixer.h"
#include <SDL.h>
#include <string>

class Sound : public Component {
    public:
        // COntrutores
        Sound(GameObject& associated);
        Sound(GameObject& associated, std::string file);
        // Destrutor
        ~Sound();
        //Métodos
        void Play (int times = 1);
        void Stop();
        void Open(std::string file);
        void Update(float dt);
        void Render();

        bool IsOpen();
        bool Is(std::string type);

    private:
        Mix_Chunk* chunk;
        int        channel;

};
#endif