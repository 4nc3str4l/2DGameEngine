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
    static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
    static void mouse_button_callback(GLFWwindow* window, int button, int action, int mods);
    static void cursor_position_callback(GLFWwindow* window, double xpos, double ypos);
    static void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
	static void framebuffer_size_callback(GLFWwindow* window, int width, int height);
private:
	GLFWwindow* window;
public:
	int width;
	int height;
	bool isResized;
	std::string title;
};
}