#include "../Headers/Game.h"
#include "../Headers/StageState.h"

int main(int argc, char** argv) {
    Game& game = Game::GetInstance();
    StageState* initialState = new StageState();
    game.Push(initialState);
    game.Run();   
    return 0;
}