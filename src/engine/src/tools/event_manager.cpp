#include "event_manager.h"

namespace le 
{

std::map<int, std::vector<voidEventCall> > EventManager::events;

void EventManager::subscribe(Event ev, voidEventCall func)
{
    events[ev].push_back(func);
}

void EventManager::unSubscribe(Event ev, voidEventCall func)
{

}

void EventManager::fire(Event ev)
{
    for(auto func : events[ev])
    {
        func();
    }
}

}