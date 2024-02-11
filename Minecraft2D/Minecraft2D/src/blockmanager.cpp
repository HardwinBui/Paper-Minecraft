#include "blockmanager.h"

BlockManager::BlockManager(SpriteRenderer *renderer)
{
	this->Renderer = renderer;
	this->perlin = new Perlin(20,100,5,12345);
	this->cameraX = 0;
	this->cameraY = 0;
	for (int i = 0; i < sizeof(blockNames)/sizeof(blockNames[0]); i++)
	{
		blockDex[i] = new Block(i, blockNames[i]);
	}

	for (int i = 0; i < 20; i++)
		printf(" % f\n", perlin->Get(i,0));
}

void BlockManager::Render()
{
	int curChunk = 0;
	// printf("%f\n", this->cameraX);
	// roughly 1:40
	curChunk = this->cameraX / 40.0f;

	GenerateChunk(curChunk);
	GenerateChunk(curChunk-1);
	GenerateChunk(curChunk+1);

	// interate through desired chucks of blocks
	for (int x = curChunk - chunkSize/2; x < curChunk + chunkSize; x++)
	{
		for (int y = minHeight; y < maxHeight; y++) 
		{
			int blockID = 0;
			/*if (this->blocks.find(std::pair<int, int>(x, y)) == this->blocks.end())
			{
				GenerateChunk(x % chunkSize);
			}*/
			blockID = this->blocks.find(std::pair<int,int>(x, y))->second;

			blockDex[blockID]->Render(this->Renderer, x, y);
		}
	}
}

void BlockManager::GenerateChunk(int chunk)
{
	if (this->chunksGenerated.find(chunk) != this->chunksGenerated.end())
		return;

	int startPos = chunk * chunkSize;
	for (int x = startPos; x < startPos + chunkSize; x++)
	{
		for (int y = minHeight; y < maxHeight; y++)
		{
			GenerateBlock(x, y);
		}
	}
	this->chunksGenerated.insert(chunk);
}

void BlockManager::GenerateBlock(int x, int y)
{
	int blockID = 0;

	// TODO: block logic here
	float noise = perlin->Get(x, y);
	if (noise > 0.5f)
		blockID = 3;
	else blockID = 2;

	/*if (y > 0) blockID = 3;
	else blockID = 0;*/

	std::pair<int, int> pos(x, y);
	this->blocks.insert(std::pair<std::pair<int, int>, int>(pos, blockID));
}

void BlockManager::UpdateCameraPosition(float x, float y)
{
	this->cameraX = x;
	this->cameraY = y;
}