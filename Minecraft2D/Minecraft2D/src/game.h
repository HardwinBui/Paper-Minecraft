#ifndef GAME_H
#define GAME_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>

enum GameState {
	GAME_ACTIVE,
	GAME_MENU
};

class Game 
{
public:
	GameState State;
	bool Keys[1024];
	unsigned int Width, Height;
	// Constructor / destructor
	Game(unsigned int wight, unsigned int height);
	~Game();
	// Init game state
	void Init();
	// Game Loop
	void ProcessInput(float dt);
	void Update(float dt);
	void Render();
};


#endif