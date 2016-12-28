#pragma once
#include "basic_config.h"

#include "sdl_engine.h"

#include <functional>

namespace Global
{
    void ErrorQuit(const char* ErrorMessage);
}

extern SDL_Window* wnd;
extern SDL_Renderer* rnd;
extern TTF_Font* font;

/// 16:9
#define WIN_WIDTH 1365
#define WIN_HEIGHT 768

extern std::function<int()> empty_call;
