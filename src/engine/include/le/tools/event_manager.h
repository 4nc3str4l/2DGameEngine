#pragma once

#include <map>
#include <functional>
#include <vector>
#include "delegate.h"
#include <string>

namespace le
{

typedef Delegate<void(const std::string&)> fileDropHandler;

class EventManager
{
public:
    static fileDropHandler onFileDropped;
};
}
