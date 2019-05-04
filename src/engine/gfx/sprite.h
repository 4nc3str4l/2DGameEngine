#pragma once

#include "memory"
#include "texture_2d.h"
#include <glm/glm.hpp>

namespace le
{
class Sprite
{
public:
    Sprite();
    Sprite(int x, int y, std::shared_ptr<Texture2D> texture);
public:
    glm::vec2 pos;
    float rot;
    glm::vec2 scale;
    glm::vec3 tint;
    std::shared_ptr<Texture2D> texture;
};

}