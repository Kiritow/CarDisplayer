#include "xbutton.h"
#include "ResourceManager.h"

struct xbutton::impl
{
    ResourceIndex normal,mouseover,pressed;
    function<int()> fn_mouseover,fn_pressed,fn_release;

    SDL_Rect rect;
    int mode;
};

xbutton::xbutton()
{
    pimpl=new impl;
    pimpl->mode=0;
    pimpl->fn_mouseover=empty_call;
    pimpl->fn_pressed=empty_call;
    pimpl->fn_release=empty_call;
}

xbutton::~xbutton()
{
    delete pimpl;
}

int xbutton::onMouseOver()
{
    printf("MouseOver.\n");
    return pimpl->fn_mouseover();
}

int xbutton::onPressed()
{
    printf("Pressed.\n");
    return pimpl->fn_pressed();
}

int xbutton::onRelease()
{
    printf("Released.\n");
    return pimpl->fn_release();
}

bool xbutton::isReady()
{
    return false;
}

int xbutton::attachEventManager(EventManager& evm)
{
    evm.add(SDL_MOUSEMOTION,[&](SDL_Event e)->int{onMouseOver();return 0;});
    evm.add(SDL_MOUSEBUTTONDOWN,[&](SDL_Event e)->int{onPressed();return 0;});
    evm.add(SDL_MOUSEBUTTONUP,[&](SDL_Event e)->int{onRelease();return 0;});
    return 0;
}

int xbutton::deal(SDL_Event e)
{
    int ret=1;
    switch(e.type)
    {
    case SDL_MOUSEMOTION:
        if(inRange(e.button.x,e.button.y))
        {
            if(pimpl->mode==0) ret=onMouseOver();
            pimpl->mode=1;
        }
        else
        {
            pimpl->mode=0;
        }
        break;
    case SDL_MOUSEBUTTONDOWN:
        if(pimpl->mode==1&&inRange(e.button.x,e.button.y))
        {
            ret=onPressed();
            pimpl->mode=2;
        }
        break;
    case SDL_MOUSEBUTTONUP:
        if(pimpl->mode==2)
        {
            ret=onRelease();
            if(inRange(e.button.x,e.button.y))
            {
                pimpl->mode=1;
            }
            else
            {
                pimpl->mode=0;
            }
        }
        break;
    }

    return ret;
}

void xbutton::setNormal(ResourceIndex idx,function<int()> callback)
{
    pimpl->normal=idx;
    pimpl->fn_release=callback;
}

void xbutton::setMouseover(ResourceIndex idx,function<int()> callback)
{
    pimpl->mouseover=idx;
    pimpl->fn_mouseover=callback;
}

void xbutton::setPressed(ResourceIndex idx,function<int()> callback)
{
    pimpl->pressed=idx;
    pimpl->fn_pressed=callback;
}

void xbutton::setRange(int x,int y,int w,int h)
{
    pimpl->rect.x=x;
    pimpl->rect.y=y;
    pimpl->rect.w=w;
    pimpl->rect.h=h;
}

bool xbutton::inRange(int x,int y)
{
    SDL_Point pp { x, y };
    return SDL_PointInRect(&pp,&(pimpl->rect));
}

void xbutton::draw()
{
    SDL_Texture* text;
    switch(pimpl->mode)
    {
        case 0:text=resmanager.GetPicture(pimpl->normal);break;
        case 1:text=resmanager.GetPicture(pimpl->mouseover);break;
        case 2:text=resmanager.GetPicture(pimpl->pressed);break;
    }
    SDL_RenderCopy(rnd,text,NULL,&(pimpl->rect));
}
