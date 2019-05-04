#include <iostream>
#include "gfx/window.h"
#include "tools/loader.h"
#include "gfx/sprite_renderer.h"

#include "tools/input.h"
#include "glm/gtc/matrix_transform.hpp"
#include "tools/maths.h"
#include "gfx/sprite.h"

int main(int argc, char** argv)
{
    auto w = le::Window{800, 600, "Lost Engine"};

	if (!w.init()) 
	{
		return -1;
	}

	le::Loader::init(argv);
	auto s = le::Loader::shader("res/shaders/sprite");
	auto texture2 = le::Loader::LoadTexture("res/textures/quad.png");
	
    // Configure shaders
    glm::mat4 projection = glm::ortho(0.0f, static_cast<GLfloat>(800), static_cast<GLfloat>(600), 0.0f, -1.0f, 1.0f);
    
	s.get()->Use();
	s.get()->SetInt("image", 0);

    s.get()->SetMat4("projection", projection);
    
	// Set render-specific controls
    auto sr = le::SpriteRenderer(*s.get());

    /* Loop until the user closes the window */
	int spriteX = 0;
	int spriteY = 0;

	const int SPRITE_NUM = 2000;
	le::Sprite sprites[SPRITE_NUM];
	for(int i = 0; i < SPRITE_NUM; i++)
	{
		sprites[i] = le::Sprite{0, 0, texture2};
		sprites[i].tint = glm::vec3(le::Maths::GetRandomFloat(), le::Maths::GetRandomFloat(), le::Maths::GetRandomFloat());
	}
	
    while (!w.isClosed())
    {
		w.clear();

		for (int i = 0; i < SPRITE_NUM; i++)
		{
			auto s = sprites[i];
			s.pos.x = le::Maths::GetRandomFloat(0, w.width);
			s.pos.y = le::Maths::GetRandomFloat(0, w.height);
			sr.DrawSprite(*s.texture.get(), s.pos, s.scale, s.rot, s.tint);
		}

		w.update();
    }

    return 0;
}