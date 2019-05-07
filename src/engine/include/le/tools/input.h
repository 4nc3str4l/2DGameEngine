#pragma once

#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>

namespace le 
{

const int MAX_KEYS = 1024;
const int MAX_BUTTONS = 32;

class Input
{
public:
	static void Initialize();
	static bool IsKeyPressed(unsigned int keycode);
	static bool IsMouseButtonPressed(unsigned int button);
	static double MousePosX;
	static double MousePosY;
	static double ScrollOffset;
	static bool keys[];
	static bool mouseButtons[];
};
}