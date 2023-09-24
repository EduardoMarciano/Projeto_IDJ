#include <fstream>
#include <iostream>
#include <ostream>
#include <sstream>
#include "../Headers/TileMap.h"

TileMap::TileMap(GameObject &associated, std::string file, TileSet *tileSet):Component(associated), tileSet(tileSet){
    Load(file);
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