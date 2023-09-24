#ifndef TileMap_H
#define TileMap_H

#include "../Headers/Component.h"
#include "../Headers/TileSet.h"
#include <string>

class TileMap: public Component{
    
    public:
        TileMap(GameObject& associated, std::string file, TileSet* tileSet);

        void Load(std::string file);
        void SetTileSet(TileSet* tileSet);
        void Render();
        void Update(float td);
        void RenderLayer(int layer, int cameraX = 0, int cameraY = 0);

        int& At(int x, int y,int z = 0);

        int GetWidth();
        int GetHeight();
        int GetDepth();

        bool Is(std::string type);

    private:
    int mapWidth;
    int mapHeight;
    int mapDepth;

    TileSet* tileSet;
    std::vector<int> tileMatrix;
};

#endif