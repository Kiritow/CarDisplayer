#include "EventManager.h"

#include <vector>
#include <map>
using namespace std;

namespace _notpublic
{

struct EventManager::impl
{
    map<decltype(SDL_Event::type),vector<EventHandlerType>> callmap;
};

EventManager::EventManager()
{
    pimpl=new impl;
}

EventManager::~EventManager()
{
    delete pimpl;
}

int EventManager::add(decltype(SDL_Event::type) type,EventHandlerType func)
{
    pimpl->callmap[type].push_back(func);
    return pimpl->callmap[type].size()-1;
}

int EventManager::deal(SDL_Event event)
{
    for(auto& pack:pimpl->callmap)
    {
        if(pack.first==event.type)
        {
            int solved=0;
            for(auto& func:pack.second)
            {
                if(func(event))
                {
                    solved=1;
                    break;
                }
            }

            return solved;
        }
    }

    return 0;
}

}/// End of namespace _notpublic


int EventManager::deal(SDL_Event event,int& running,int& need_update)
{
    /// Deal With System Events.
    if(event.type==SDL_QUIT)
    {
        need_update=1;
        running=0;
        return 1;
    }
    /// Deal with User Events.
    return _notpublic::EventManager::deal(event);
}

int EventManager::pollNext(int& running,int& need_update)
{
    SDL_Event e;
    if(SDL_PollEvent(&e))
    {
        return deal(e,running,need_update);
    }
    return -1;
}
