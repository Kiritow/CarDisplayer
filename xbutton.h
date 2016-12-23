#pragma once
#include "config.h"
#include "EventManager.h"

class xbutton
{
public:
    xbutton();
    ~xbutton();
    void setSensor(int LUx,int LUy,int RDx,int RDy);
    int attachEventManager(EventManager& evm);
    bool isReady();
    void onMouseOver();/// Normal->MouseOver
    void onPressed();/// MouseOver->PressedDown
    void onRelease();/// PressedDown->Normal
private:
    struct impl;
    impl* pimpl;
};
