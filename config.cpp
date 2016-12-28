#include "config.h"
SDL_Window* wnd=NULL;
SDL_Renderer* rnd=NULL;
TTF_Font* font=NULL;

namespace Global
{
    void ErrorQuit(const char* ErrorMessage)
    {
        mlog(ErrorMessage);
        exit(0);
    }
}

function<int()> empty_call=[&](){return 1;};
