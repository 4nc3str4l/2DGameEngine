#include <iostream>
#include "gfx/window.h"
#include "tools/loader.h"

int main(int argc, char** argv)
{
    auto w = le::Window{800, 600, "Lost Engine"};

	if (!w.init()) 
	{
		return -1;
	}

	le::Loader::init(argv);
	auto s = le::Loader::shader("res/shaders/sprite");
	auto s2 = le::Loader::shader("res/shaders/sprite");

    /* Loop until the user closes the window */
    while (!w.isClosed())
    {
		w.clear();
		w.update();
    }

    return 0;
}