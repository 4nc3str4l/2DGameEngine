#pragma once

#include "application.h"

namespace le
{

class LostEngine
{
public:
    LostEngine(char **argv, Application* application);
    ~LostEngine();
    void start();
private:
    Application* app;
};
}