#pragma once
#include "basic_config.h"

#include "sdl_engine.h"

namespace Global
{
    void ErrorQuit(const char* ErrorMessage);
}

extern SDL_Window* wnd;
extern SDL_Renderer* rnd;
extern TTF_Font* font;

#define WIN_WIDTH 1024
#define WIN_HEIGHT 768
