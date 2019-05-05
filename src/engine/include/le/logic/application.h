#pragma once

#include "../gfx/window.h"

namespace le
{
class Application
{
public:
    Application(const std::string& title, int width, int height)
    {
        this->title = title;
        this->width = width;
        this->height = height;
    }

    virtual void init(Window* _window) = 0;
    virtual void update(float _delta, Window* _window) = 0;
    virtual void render(Window* _window) = 0;

public:
    std::string title;
    int width;
    int height;
};  
}