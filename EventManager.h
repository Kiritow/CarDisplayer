#pragma once
#include "config.h"
#include <functional>
using namespace std;

typedef function<int(SDL_Event)> EventHandlerType;

namespace _notpublic
{

class EventManager
{
public:
    EventManager();
    ~EventManager();
    int deal(SDL_Event event);
    int add(decltype(SDL_Event::type) type,EventHandlerType func);
private:
    struct impl;
    impl* pimpl;
};

}/// End of namespace _notpublic

class EventManager : public _notpublic::EventManager
{
public:
    int deal(SDL_Event event,int& running,int& need_update);
    int pollNext(int& running,int& need_update);
};
