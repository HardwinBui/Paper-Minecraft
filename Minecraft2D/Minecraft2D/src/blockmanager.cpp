#include "blockmanager.h"

BlockManager::BlockManager(SpriteRenderer *renderer)
{
	this->Renderer = renderer;
	for (int i = 0; i < sizeof(blockNames)/sizeof(blockNames[0]); i++)
	{
		blockDex[i] = new Block(i, blockNames[i]);
	}

	GenerateChunk(0);
	GenerateChunk(1);
	GenerateChunk(2);
}

void BlockManager::Render()
{
	// interate through desired chucks of blocks

	for (int x = 0; x < 20; x++)
	{
		for (int y = 0; y < maxHeight; y++) 
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
	int startPos = chunk * chunkSize;
	for (int x = startPos; x < startPos + chunkSize; x++)
	{
		for (int y = 0; y < maxHeight; y++)
		{
			GenerateBlock(x, y);
		}
	}
}

void BlockManager::GenerateBlock(int x, int y)
{
	int blockID;

	// TODO: block logic here
	if (y > 20) blockID = 0;
	else blockID = 3;

	std::pair<int, int> pos(x, y);
	this->blocks.insert(std::pair<std::pair<int, int>, int>(pos, blockID));

	/*int test = this->blocks.find(std::pair<int, int>(x, y))->second;
	printf("%d\n", test);*/
}