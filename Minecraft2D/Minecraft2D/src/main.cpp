#include <iostream>	
#include <glad/glad.h>
#include <GLFW/glfw3.h>

int main() 
{
	glfwInit();

	int width = 800;
	int height = 600;

	GLFWwindow* window = glfwCreateWindow(width, height, "Minecraft2D", NULL, NULL);
	if (window == NULL)
	{
		std::cout << "Failed to make window" << std::endl;
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);
	
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) 
	{
		std::cout << "Failed to init GLAD" << std::endl;
		return -1;
	}
	glViewport(0, 0, width, height);
	
	while (!glfwWindowShouldClose(window))
	{
		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glfwTerminate();
	return 0;
}