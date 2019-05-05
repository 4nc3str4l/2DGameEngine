
#include "Timer.h"

namespace le 
{

float Timer::deltaTime = 0.0f;
float Timer::lastFrame = 0.0f;

void Timer::update() 
{
	float currentFrame = glfwGetTime();
	deltaTime = currentFrame - lastFrame;
	lastFrame = currentFrame;
}

}