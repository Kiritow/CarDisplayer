#pragma once
#include<iostream>
#include<string>
#include <SDL2/SDL.h>
#undef main
#include <SDL2/SDL_image.h>
using namespace std;
class abstract_car
{
public:
    virtual void show_history()=0;
    virtual void show_picture()=0;
};


