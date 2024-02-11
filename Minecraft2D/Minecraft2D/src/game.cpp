#include "game.h"
#include "utils/resource_manager.h"
#include "utils/sprite_renderer.h"
#include "camera.h"
#include "blockmanager.h"

SpriteRenderer *Renderer;
Camera camera;
BlockManager *blockManager;

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
    // camera/view transformation
    camera = (glm::vec3(20.1f, 10.0f, 0.0f));
    glm::mat4 view = camera.GetViewMatrix();
    ResourceManager::GetShader("sprite").SetMatrix4("view", view);

    // set render-specific controls
    Shader myShader = ResourceManager::GetShader("sprite");
    Renderer = new SpriteRenderer(myShader);    
    // load textures
    ResourceManager::LoadTexture("textures/grass.jpg", true, "grass");
    ResourceManager::LoadTexture("textures/dirt.jpg", true, "dirt");
    ResourceManager::LoadTexture("textures/sand.jpeg", true, "sand");
    ResourceManager::LoadTexture("textures/stone.png", true, "stone");

    blockManager = new BlockManager(Renderer);
}

void Game::Update(float dt)
{
    // update player movement
    // update camera movement
    blockManager->UpdateCameraPosition(camera.GetXPosition(), camera.GetXPosition());
}

void Game::ProcessInput(float dt)
{
	//if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
	//{
	//	// Do something here
	//}

    if (this->Keys[GLFW_KEY_A]){
        camera.ProcessKeyboard(LEFT, dt);
        glm::mat4 view = camera.GetViewMatrix();
        ResourceManager::GetShader("sprite").SetMatrix4("view", view);
    }
    else if (this->Keys[GLFW_KEY_D]) {
        camera.ProcessKeyboard(RIGHT, dt);
        glm::mat4 view = camera.GetViewMatrix();
        ResourceManager::GetShader("sprite").SetMatrix4("view", view);
    }

    if (this->Keys[GLFW_KEY_W]) {
        camera.ProcessKeyboard(UP, dt);
        glm::mat4 view = camera.GetViewMatrix();
        ResourceManager::GetShader("sprite").SetMatrix4("view", view);
    }
    else if (this->Keys[GLFW_KEY_S]) {
        camera.ProcessKeyboard(DOWN, dt);
        glm::mat4 view = camera.GetViewMatrix();
        ResourceManager::GetShader("sprite").SetMatrix4("view", view);
    }
}

//void DrawBlock(std::string blockType, float x, float y)
//{
//    float blockSize = 40.f;
//    Texture2D texture = ResourceManager::GetTexture(blockType);
//    Renderer->DrawSprite(texture, glm::vec2(x*blockSize ,y*blockSize), glm::vec2(blockSize, blockSize));
//}

void Game::Render()
{
    //Texture2D texture = ResourceManager::GetTexture("face");
    //Renderer->DrawSprite(texture, glm::vec2(200.0f, 200.0f), glm::vec2(300.0f, 400.0f), 45.0f, glm::vec3(0.0f, 1.0f, 0.0f));
    //Renderer->DrawSprite(texture, glm::vec2(200.0f, 200.0f), glm::vec2(40.0f, 40.0f), 0.0f);
    
    /*DrawBlock("dirt", 0, 1);
    DrawBlock("grass", 0, 0);
    DrawBlock("stone", 0, 0);
    DrawBlock("stone", 1, 0);*/

    blockManager->Render();
}