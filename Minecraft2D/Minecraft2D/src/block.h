#ifndef BLOCK_H
#define BLOCK_H

/*
    0: AIR BLOCK
    1: GRASS BLOCK
    2: DIRT BLOCK
    3: STONE BLOCK
    4: SAND BLOCK
*/

#include "utils/sprite_renderer.h"
#include "utils/resource_manager.h"

const float blockSize = 40.f;

class Block
{
public:
    Block(int id = 0, std::string blockName = "air");
    void Render(SpriteRenderer* Renderer, int x, int y);

private:
    int id;
    std::string blockName;
};

#endif