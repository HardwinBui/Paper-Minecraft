#include "block.h"

Block::Block(int id, std::string blockName)
{
	this->id = id;
	this->blockName = blockName;
}

void Block::Render(SpriteRenderer* Renderer, int x, int y)
{
	if (this->blockName == "air") return;
	Texture2D texture = ResourceManager::GetTexture(this->blockName);
	Renderer->DrawSprite(texture, glm::vec2(x * blockSize, y * blockSize), glm::vec2(blockSize, blockSize));
}