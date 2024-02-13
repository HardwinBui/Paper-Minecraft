#include "blockmanager.h"

BlockManager::BlockManager(SpriteRenderer *renderer)
{
	this->Renderer = renderer;
	this->cameraX = 0;
	this->cameraY = 0;
	for (int i = 0; i < sizeof(blockNames)/sizeof(blockNames[0]); i++)
	{
		blockDex[i] = new Block(i, blockNames[i]);
	}
	this->perlin = new Perlin();
}

void BlockManager::Render()
{
	int curChunk = 0;
	// 1:40 ratio for distance:camera
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
			blockID = this->blocks[std::pair<int, int>(x, y)];
			// display water
			if (blockID == 0 && y > waterLevel)
			{
				blockID = 5;
			}

			blockDex[blockID]->Render(this->Renderer, x, y);
		}
	}
}

void BlockManager::UpdateCameraPosition(float x, float y)
{
	this->cameraX = x;
	this->cameraY = y;
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
	DecorateChunk(chunk);
}

void BlockManager::GenerateBlock(int x, int y)
{
	int blockID = 0;

	// Get perlin noise to determine height of terrain in column
	float noise = this->perlin->PerlinNoise(x, y);
	float modifier = 0.25f;
	float amplitude = 7;
	if (y * modifier < noise * amplitude)
		blockID = 0;
	else blockID = 3;

	std::pair<int, int> pos(x, y);
	this->blocks[pos] = blockID;
}

void BlockManager::DecorateChunk(int chunk)
{
	int startPos = chunk * chunkSize;
	for (int x = startPos; x < startPos + chunkSize; x++)
	{
		bool foundSurface = false;
		int depth = 3 - (rand() % 3);
		int curDepth = 0;

		for (int y = minHeight; y < maxHeight; y++)
		{
			// spawn ores
			if (curDepth > depth && foundSurface)
			{
				float abundance = 3;
				float noise = this->perlin->PerlinNoise(x*abundance, y*abundance);
				if (noise > 0.6f && y < coalHeight)
				{
					std::pair<int, int> pos(x, y);
					this->blocks[pos] = 7;
				}
				else if (noise < 0.3f)
				{
					std::pair<int, int> pos(x, y);
					this->blocks[pos] = 6;
				}
			}
			// spawn dirt
			else if (foundSurface)
			{
				std::pair<int, int> pos(x, y);
				this->blocks[pos] = 2;
				curDepth += 1;
			}
			// spawn grass or sand (based on water height)
			else if (this->blocks.find(std::pair<int, int>(x, y))->second != 0)
			{	
				std::pair<int, int> pos(x, y);
				this->blocks[pos] = y > waterLevel+1 ? 4 : 1;				
				foundSurface = true;
			}
		}
	}
}