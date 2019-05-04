#include <iostream>
#include "gfx/window.h"
#include "tools/loader.h"
#include "gfx/sprite_renderer.h"

#include "tools/input.h"
#include "glm/gtc/matrix_transform.hpp"
#include "tools/maths.h"
#include "gfx/sprite.h"
#include <vector>

#include "gfx/text_renderer.h"


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
    
	s->Use();
	s->SetInt("image", 0);

    s->SetMat4("projection", projection);
    
	// Set render-specific controls
    auto sr = le::SpriteRenderer(*s);

    /* Loop until the user closes the window */
	int spriteX = 0;
	int spriteY = 0;

	const int SPRITE_NUM = 2000;

	std::vector<le::Sprite*> sprites;
	for(int i = 0; i < SPRITE_NUM; i++)
	{
		sprites.push_back(new le::Sprite{0, 0, texture2});
	}	

	auto Text = new le::TextRenderer(w.width, w.height);
    Text->Load("res/fonts/OCRAEXT.TTF", 24);

    while (!w.isClosed())
    {
		w.clear();

		s->SetMat4("projection", projection);
		for (le::Sprite* s : sprites)
		{
			s->pos.x = le::Maths::GetRandomFloat(0, w.width);
			s->pos.y = le::Maths::GetRandomFloat(0, w.height);
			s->tint = glm::vec3(le::Maths::GetRandomFloat(), le::Maths::GetRandomFloat(), le::Maths::GetRandomFloat());
		}

		sr.Render(sprites);

		Text->RenderText("Text Rendering!!!", 250.0f, w.height / 2, 1.0f);
		
		w.update();
    }

	le::Loader::FreeResources();
	delete Text;

    return 0;
}