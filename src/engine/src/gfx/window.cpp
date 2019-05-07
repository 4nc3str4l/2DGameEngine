#include "window.h"
#include <iostream>
#include "../tools/input.h"
#include "../tools/log.h"
#include "event_manager.h"

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

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
	glfwSwapInterval(0);

	#ifdef __APPLE__
		glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	#endif

	glfwSetWindowUserPointer(window, this);
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
	glfwSetKeyCallback(window, key_callback);
	glfwSetMouseButtonCallback(window, mouse_button_callback);
	glfwSetCursorPosCallback(window, cursor_position_callback);
	glfwSetScrollCallback(window, scroll_callback);
	glfwSetDropCallback(window, drop_callback);
	
	glEnable(GL_DEPTH_TEST);
	
	// Allow alpha blending
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_BLEND);


	// Define the viewport dimensions
    glViewport(0, 0, this->width, this->height);
}

void Window::clear() 
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void Window::update()
{
	isResized = false;

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

void Window::key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    Window* win = (Window*) glfwGetWindowUserPointer(window);
    Input::keys[key] = action != GLFW_RELEASE;
}

void Window::mouse_button_callback(GLFWwindow* window, int button, int action, int mods)
{
    Window* win = (Window*) glfwGetWindowUserPointer(window);
    Input::mouseButtons[button] = action != GLFW_RELEASE;
}

void Window::cursor_position_callback(GLFWwindow* window, double xpos, double ypos)
{
    Input::MousePosX = xpos;
    Input::MousePosY = ypos;
}

void Window::scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
    Input::ScrollOffset = yoffset;
}

void Window::framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    Window* ownWindow = (Window*)glfwGetWindowUserPointer(window);
    ownWindow->width = width;
    ownWindow->height = height;
	LOG_INFO(ownWindow->width, ", ",  ownWindow->height);
	ownWindow->isResized = true;
	glViewport(0, 0, width, height);
}

void Window::drop_callback(GLFWwindow* window, int count, const char** paths)
{
	for (int i = 0;  i < count;  i++)
	{
		EventManager::fire(Event::drop_file);
		LOG_MESSAGE(paths[i]);
	}
}

}