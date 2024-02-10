#include "game.h"
#include "resource_manager.h"
#include "sprite_renderer.h"

SpriteRenderer *Renderer;

Game::Game(unsigned int width, unsigned int height)
	: State(GAME_ACTIVE), Keys(), Width(width), Height(height)
{
    
}

Game::~Game()
{
    delete Renderer;
}

void Game::Init()
{
    // load shaders
    ResourceManager::LoadShader("shaders/sprite.vs", "shaders/sprite.frag", nullptr, "sprite");
    // configure shaders
    glm::mat4 projection = glm::ortho(0.0f, static_cast<float>(this->Width),
        static_cast<float>(this->Height), 0.0f, -1.0f, 1.0f);
    ResourceManager::GetShader("sprite").Use().SetInteger("image", 0);
    ResourceManager::GetShader("sprite").SetMatrix4("projection", projection);
    // set render-specific controls
    Shader myShader = ResourceManager::GetShader("sprite");
    Renderer = new SpriteRenderer(myShader);    
    // load textures
    ResourceManager::LoadTexture("textures/moom.png", true, "face");
}

void Game::Update(float dt)
{
    Render();
}

void Game::ProcessInput(float dt)
{
	//if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
	//{
	//	// Do something here
	//}
}

void Game::Render()
{
    Texture2D texture = ResourceManager::GetTexture("face");
    Renderer->DrawSprite(texture, glm::vec2(200.0f, 200.0f), glm::vec2(300.0f, 400.0f), 45.0f, glm::vec3(0.0f, 1.0f, 0.0f));
}