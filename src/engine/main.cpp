#include <iostream>
#include "window.h"
#include "loader.h"
#include "sprite_renderer.h"

#include "input.h"
#include "glm/gtc/matrix_transform.hpp"
#include "maths.h"
#include "sprite.h"
#include <vector>

#include "text_renderer.h"
#include "log.h"


int main(int argc, char** argv)
{
    auto w = le::Window{800, 600, "Lost Engine"};

	if (!w.init()) 
	{
		return -1;
	}

	le::Loader::init(argv);
	auto s = le::Loader::shader("res/shaders/light_sprite");
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

		s->Use();
		s->SetVec2("light_pos", glm::vec2(le::Maths::ReprojectRange(0, w.width, -1, 1, le::Input::MousePosX), le::Maths::ReprojectRange(0, w.height, -1, 1, w.height - le::Input::MousePosY)));
		s->SetMat4("projection", projection);
		for (le::Sprite* s : sprites)
		{
			s->pos.x = le::Maths::GetRandomFloat(spriteX, w.width);
			s->pos.y = le::Maths::GetRandomFloat(spriteY, w.height);
			s->tint = glm::vec3(le::Maths::GetRandomFloat(), le::Maths::GetRandomFloat(), le::Maths::GetRandomFloat());
		}

		if(le::Input::IsKeyPressed(GLFW_KEY_W))
		{
			spriteX += 1;
		}

		if(le::Input::IsKeyPressed(GLFW_KEY_S))
		{
			spriteX -= 1;
		}
		

		if(le::Input::IsKeyPressed(GLFW_KEY_A))
		{
			spriteY -= 1;
		}
		
		if(le::Input::IsKeyPressed(GLFW_KEY_D))
		{
			spriteY -= 1;
		}
		

		sr.Render(sprites);

		Text->RenderText("Text Rendering!!!", spriteX, w.height / 2, 1.0f);
		
		w.update();
    }

	le::Loader::FreeResources();
	delete Text;

    return 0;
}