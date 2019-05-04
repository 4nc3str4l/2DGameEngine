#pragma once

#include "memory"
#include "texture_2d.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

namespace le
{
class Sprite
{
public:
    Sprite();
    Sprite(int x, int y, Texture2D* texture);
	void ComputeModel();
public:
    glm::vec3 pos;
    float rot;
    glm::vec3 scale;
    glm::vec3 tint;
	Texture2D* texture;
    glm::mat4 model;
private:
    static glm::vec3 rotVec;
    static glm::vec3 helper;
};

}