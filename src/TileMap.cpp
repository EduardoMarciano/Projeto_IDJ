#include <fstream>
#include <iostream>
#include <ostream>
#include <sstream>
#include "../Headers/Camera.h"
#include "../Headers/TileMap.h"

TileMap::TileMap(GameObject &associated, std::string file, TileSet *tileSet):Component(associated), tileSet(tileSet){
    TileMap::Load(file.c_str());
    
}
void TileMap::Load(std::string file) {
    std::ifstream mapFile(file);
    if (!mapFile.is_open()) {
        std::cerr << "Erro ao abrir o arquivo de mapa: " << file << std::endl;

    }else{ 
        char separator;
        mapFile >> mapWidth >> separator >> mapHeight >> separator >> mapDepth >> separator;
        mapFile.ignore();
        
        tileMatrix.resize(mapWidth * mapHeight * mapDepth);
        int tile;
        for (int i = 0; i < (tileMatrix.size()); i++){
            mapFile >> tile >> separator;
            tileMatrix[i] = tile - 1;
        }
    }
    mapFile.close();
}
void TileMap::SetTileSet(TileSet* newTileSet){
    tileSet = newTileSet;
}

int& TileMap::At(int x, int y, int z){
    int index = x + (y * mapWidth) + (z * mapWidth * mapHeight);
    return tileMatrix[index];
}

void TileMap::RenderLayer(int layer, int cameraX, int cameraY) {
    if (layer < 0 || layer > mapDepth) {
        return;
    }

    int tileWidth = tileSet->GetTileWidth();
    int tileHeight = tileSet->GetTileHeight();

    for (int y = 0; y < mapHeight; y++) {
        for (int x = 0; x < mapWidth; x++) {
            int tileIndex = At(x, y, layer);

            if (tileIndex >= 0) {
                int renderX = x * tileWidth - cameraX;
                int renderY = y * tileHeight - cameraY;
                tileSet->RenderTile(tileIndex, renderX, renderY);
            }
        }
    }
}

void TileMap::Render() {
    int mapWidth = GetWidth();
    int mapHeight = GetHeight();
    int mapDepth = GetDepth();

    for (int layer = 0; layer < mapDepth; layer++) {
        RenderLayer(layer, Camera::pos.x, Camera::pos.y);
    }
}

int TileMap::GetHeight(){
    return mapHeight;
}
int TileMap::GetWidth(){
    return mapWidth;
}
int TileMap::GetDepth(){
    return mapDepth;
}
bool TileMap::Is(std::string type){
    if (type == "TileMap"){
        return true;
    }else{
        return false;
    }
}
void TileMap::Update(float dt) {
    return;
}