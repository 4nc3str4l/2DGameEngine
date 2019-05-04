#include "sprite.h"

namespace le
{
Sprite::Sprite(){}
Sprite::Sprite(int x, int y, std::shared_ptr<Texture2D> texture)
{
    this->pos.x = x; 
    this->pos.y = y;
    this->texture = texture;
    this->rot = 0;
    this->scale.x = texture.get()->Width;
    this->scale.y = texture.get()->Height;
    this->tint.x = 1;
    this->tint.y = 1;
    this->tint.z = 1;
}
}