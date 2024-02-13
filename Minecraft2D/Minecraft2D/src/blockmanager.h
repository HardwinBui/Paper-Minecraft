#ifndef BLOCKMANAGER_H
#define BLOCKMANAGER_H

/*
    0: AIR BLOCK
    1: GRASS BLOCK
    2: DIRT BLOCK
    3: STONE BLOCK
    4: SAND BLOCK
*/

#include <map>
#include <vector>
#include <utility>
#include "utils/sprite_renderer.h"
#include "block.h"
#include <unordered_set>
#include "utils/perlin.h"

const int chunkSize = 50;
const int maxHeight = 50;// 64;
const int minHeight = -5;//-64;
const int waterLevel = 14;
const int coalHeight = 23;

const std::string blockNames[8] = {
    "air",
    "grass",
    "dirt",
    "stone",
    "sand",
    "water",
    "iron",
    "coal",
};

class BlockManager
{
public:
    BlockManager(SpriteRenderer* renderer);
    void UpdateCameraPosition(float x, float y);
    void Render();

private:

    SpriteRenderer* Renderer;
    Perlin* perlin;
    Block *blockDex[sizeof(blockNames) / sizeof(blockNames[0])];
    std::map<std::pair<int, int>, int> blocks;
    std::unordered_set<int> chunksGenerated;
    float cameraX, cameraY;

    void GenerateChunk(int chunk); // add more blocks into the map
    void GenerateBlock(int x, int y);
    void DecorateChunk(int chunk);

};

#endif