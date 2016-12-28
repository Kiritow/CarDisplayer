#pragma once
#include "config.h"
#include "EventManager.h"
#include "ResourceManager.h"

class xbutton
{
public:
    xbutton();
    ~xbutton();
    void setSensor(int LUx,int LUy,int RDx,int RDy);
    int attachEventManager(EventManager& evm);
    bool isReady();
    int onMouseOver();/// Normal->MouseOver
    int onPressed();/// MouseOver->PressedDown
    int onRelease();/// PressedDown->Normal

    void setNormal(ResourceIndex idx,function<int()> callback);
    void setMouseover(ResourceIndex idx,function<int()> callback);
    void setPressed(ResourceIndex idx,function<int()> callback);

    void setRange(int x,int y,int w,int h);

    bool inRange(int x,int y);

    int deal(SDL_Event e);
    void draw();

private:
    struct impl;
    impl* pimpl;
};
