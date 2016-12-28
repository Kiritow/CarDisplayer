#include "sensor.h"

struct sensor::impl
{
    SDL_Rect rect;
};

sensor::sensor(int LUx,int LUy,int RDx,int RDy)
{
    pimpl=new impl;
    pimpl->rect.x=LUx;
    pimpl->rect.y=LUy;
    pimpl->rect.w=RDx-LUx;
    pimpl->rect.h=RDy-LUy;
}

bool sensor::inrange(int x,int y)
{
    SDL_Point point;
    point.x=x;
    point.y=y;
    return SDL_PointInRect(&point,& (pimpl->rect) );
}

sensor::~sensor()
{
    delete pimpl;
}

void sensor::setMiddle(int* px,int* py)
{
    *px=pimpl->rect.x+pimpl->rect.w/2;
    *py=pimpl->rect.y+pimpl->rect.h/2;
}

void sensor::setMiddle(int& val_x,int& val_y)
{
    val_x=pimpl->rect.x+pimpl->rect.w/2;
    val_y=pimpl->rect.y+pimpl->rect.h/2;
}
