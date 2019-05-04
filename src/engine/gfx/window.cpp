#include "window.h"
#include <iostream>

namespace le
{

Window::Window(const int width, const int height, const std::string& title)
{
	this->width = width;
	this->height = height;
	this->title = title;
}

int Window::init()
{
	/* Initialize the library */
	if (!glfwInit())
		return -1;

	/* Create a windowed mode window and its OpenGL context */
	window = glfwCreateWindow(this->width, this->height, this->title.c_str(), NULL, NULL);
	if (!window)
	{
		glfwTerminate();
		return -1;
	}

	/* Make the window's context current */
	glfwMakeContextCurrent(window);

	// Init glad
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		return -1;
	}

	// Multisampling
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
	
	glfwWindowHint(GLFW_SAMPLES, 4);
	glEnable(GL_MULTISAMPLE);  
	glEnable(GL_DEPTH_TEST);

	// Define the viewport dimensions
    glViewport(0, 0, this->width, this->height);
}

void Window::clear() 
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void Window::update()
{
	/* Swap front and back buffers */
	glfwSwapBuffers(this->window);

	/* Poll for and process events */
	glfwPollEvents();
}

bool Window::isClosed() 
{	
	return glfwWindowShouldClose(this->window);
}

Window::~Window()
{
	glfwDestroyWindow(this->window);
	glfwTerminate();
}
}