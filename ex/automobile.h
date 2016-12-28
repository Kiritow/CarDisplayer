#pragma once
#include "car.h"
using namespace std;
class automobile:virtual public car   ///小轿车
{
public:
    automobile();
    void show_history(int p);
    void show_picture(int p);
    void show_argument(int p);
    void show_game();///use in game
    ~automobile(){}
protected:
    string TM;          ///车牌
    string wheel_base;  ///轴距（车辆前后轮中心距离：决定乘客空间大小）
    string wheel_track; ///轮距（车辆两前轮/后轮之间距离）
    string Luggage;     ///行李舱容积（行李箱的载物能力）
    string turning_diameter;///最小转弯直径
    string max_speed;   ///最高速度
    string biansuxiang; ///变速箱
};
