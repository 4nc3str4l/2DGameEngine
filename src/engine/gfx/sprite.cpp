#include "sprite.h"

namespace le
{
glm::vec3 Sprite::rotVec(0, 0, 1);
glm::vec3 Sprite::helper(0, 0, 1);

Sprite::Sprite(){}
Sprite::Sprite(int x, int y, Texture2D* texture)
{
    this->pos.x = x; 
    this->pos.y = y;
    this->pos.z = 0;
    this->texture = texture;
    this->rot = 0;
	this->scale.x = texture->Width;
	this->scale.y = texture->Height;
    this->scale.z = 0;
    this->tint.x = 1;
    this->tint.y = 1;
    this->tint.z = 1;
    this->model = glm::mat4(1.0);
}

void Sprite::ComputeModel()
{
        model[0][0] = 1.0f;
        model[1][0] = 0.0f;
        model[2][0] = 0.0f;
        model[3][0] = 0.0f;

        model[0][1] = 0.0f;
        model[1][1] = 1.0f;
        model[2][1] = 0.0f;
        model[3][1] = 0.0f;

        model[0][2] = 0.0f;
        model[1][2] = 0.0f;
        model[2][2] = 1.0f;
        model[3][2] = 0.0f;

        model[0][3] = 0.0f;
        model[1][3] = 0.0f;
        model[2][3] = 0.0f;
        model[3][3] = 1.0f;

        model = glm::translate(model, pos);
		helper.x = 0.5f * scale.x;
		helper.y = 0.5f * scale.y;
		helper.z = 0;
        model = glm::translate(model, helper);
        model = glm::rotate(model, rot, rotVec);

        helper.x = -0.5f * scale.x;
        helper.y = -0.5f * scale.y;
        helper.z = 0;
        model = glm::translate(model, helper);
        model = glm::scale(model, scale);
}

}