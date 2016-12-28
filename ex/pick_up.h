#pragma once
#include"automobile.h"
#include"truck.h"
using namespace std;
class pick_up:public automobile,public truck
{
public:
    pick_up();
    void show_history();
    void show_picture();
    void show_argument();
    ~pick_up(){}
private:
    int fuck_all;
};
