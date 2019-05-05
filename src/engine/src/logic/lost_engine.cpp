#include "lost_engine.h"
#include "../tools/loader.h"
#include "../tools/log.h"

namespace le
{
LostEngine::LostEngine(char **argv, Application* application)
{
    Loader::init(argv);
    this->app = application;
}

void LostEngine::start()
{
    auto w = le::Window{app->width, app->height, app->title};
    if (!w.init()) 
	{
        LOG_FAIL("Could not init window");
        return;
	}

    this->app->init(&w);

    while (!w.isClosed())
    {
        // TODO: GET REAL DELTA
        w.clear();
        this->app->update(0.1f, &w);
        this->app->render(&w);
		w.update();
    }
}

LostEngine::~LostEngine()
{
    delete app;
    le::Loader::FreeResources();
}
}