#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <string>

namespace le
{
class Window
{
public:
    Window(const int width, const int height, const std::string& title);
	~Window();
	int init();
	void clear();
	void update();
	bool isClosed();
private:
	GLFWwindow* window;
public:
	int width;
	int height;
	std::string title;
};
}