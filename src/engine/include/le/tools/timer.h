#pragma once
#include "GLFW/glfw3.h"

namespace le 
{
class Timer
{
public:
    static void update();
public:
    static float deltaTime;
private:
    static float lastFrame;
};
}

