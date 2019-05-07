#pragma once

#include <map>
#include <functional>
#include <vector>

namespace le
{

typedef std::function<void()> voidEventCall;
enum Event { drop_file };

class EventManager
{
public:
    static void subscribe(Event ev, voidEventCall func);
    static void unSubscribe(Event ev, voidEventCall func);
    static void fire(Event ev);
private:
    static std::map<int, std::vector<voidEventCall> > events;
};
}
