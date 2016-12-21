#pragma once

#include <cstdio>
#include <cstdlib>
#include <cstring>

using namespace std;

#include "SDL2/SDL.h"
#undef main

#include "SDL2/SDL_ttf.h"
#include "SDL2/SDL_image.h"
#include "SDL2/SDL_Mixer.h"

class NonCopyable
{
public:
    NonCopyable()=default;
    ~NonCopyable()=default;
    NonCopyable(const NonCopyable&)=delete;
    NonCopyable& operator = (const NonCopyable&)=delete;
};

extern FILE* _log_fp;

#ifdef _WINDOW_PROGRAM
#define mlog(fmt,args...) fprintf(_log_fp,fmt "\n",##args);fflush(_log_fp)
#else
#define mlog(fmt,args...) printf(fmt,##args);printf("\n")
#endif
