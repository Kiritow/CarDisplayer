#include "xbutton.h"

xbutton::xbutton()
{

}

xbutton::~xbutton()
{

}

void xbutton::onMouseOver()
{
    printf("MouseOver.\n");
}

void xbutton::onPressed()
{
    printf("Pressed.\n");
}

void xbutton::onRelease()
{
    printf("Released.\n");
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
