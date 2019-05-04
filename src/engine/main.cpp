#include <iostream>
#include "gfx/window.h"

int main(void)
{
    auto w = le::Window{800, 600, "Lost Engine"};
	
	if (!w.init()) 
	{
		return -1;
	}

    /* Loop until the user closes the window */
    while (!w.isClosed())
    {
		w.clear();
		w.update();
    }

    return 0;
}