#pragma once
#include"car.h"
using namespace std;
class truck:virtual public car
{
public:
    truck();
    void show_history();
    void show_picture();
    void show_argument();
    ~truck(){}
protected:
    string ranyouleixing;   ///燃油类型
    string luntaileixing;   ///轮胎类型
    string leixing;         ///车类型
    string zaizhongliang;   ///载重量
    string zhoushu;         ///轴心数
    string kezhuangzaiwu;   ///装载物品
    string zhidongqi;       ///制动
};
