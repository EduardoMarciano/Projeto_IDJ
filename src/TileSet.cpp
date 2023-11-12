#include <iostream>
#include "../Headers/TileSet.h"

TileSet::TileSet (int Width,    int Height, std::string file){
    GameObject *object = new GameObject();
    tileSet = new Sprite(*object);

    tileHeight = Height;
    tileWidth  = Width;

    tileSet->Open(file);
    if (tileSet->IsOpen()){
        rows = tileSet->GetHeight()/tileHeight;
        columns = tileSet->GetWidth()/tileWidth;
    }else {
        std::cerr << "Erro ao carregar música: " << SDL_GetError() << std::endl;
    }
}

void TileSet::RenderTile(unsigned index, float x, float y){
    if ((0 <= index) and (index <= (rows*columns - 1))){

        int tileX = (index % columns) * tileWidth;
        int tileY = (index / columns) * tileHeight;
        
        tileSet->SetClip(tileX, tileY, tileWidth, tileHeight);
        tileSet->Render((int) x, (int) y);
    
    }else {
        std::cerr << "Índice de tile inválido: " << index << std::endl;
    }
}
int TileSet::GetTileHeight(){
    return tileHeight;
}

int TileSet::GetTileWidth(){
    return tileWidth;
}