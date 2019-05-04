#include <iostream>
#include "gfx/window.h"
#include "tools/loader.h"
#include "gfx/sprite_renderer.h"

#include "glm/gtc/matrix_transform.hpp"

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
    while (!w.isClosed())
    {
		w.clear();
		sr.DrawSprite(*texture2.get(), 
        glm::vec2(1, 1), glm::vec2(64, 64), 45.0f, glm::vec3(0.0f, 1.0f, 0.0f));
		w.update();
    }

    return 0;
}