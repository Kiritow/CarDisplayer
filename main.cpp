#include "mini_engine_min.h"




int main()
{
    mlog("Program Begin.");
    wnd=SDL_CreateWindow("CarDisplayer",SDL_WINDOWPOS_CENTERED,SDL_WINDOWPOS_CENTERED,WIN_WIDTH,WIN_HEIGHT,SDL_WINDOW_SHOWN);
    rnd=SDL_CreateRenderer(wnd,-1,SDL_RENDERER_ACCELERATED|SDL_RENDERER_PRESENTVSYNC);
    font=TTF_OpenFont("msyh.ttf",18);
    mlog("Window Opened. Renderer Ready. Font Ready.");
    animemanager.setRenderer(rnd);
    Game::Main();
    mlog("Start Finalize...");
    TTF_CloseFont(font);
    SDL_DestroyRenderer(rnd);
    SDL_DestroyWindow(wnd);
    mlog("Program Finish.");
    return 0;
}
