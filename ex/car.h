#pragma once
#include <iostream>
#include <string>
#include "abstract_car.h"
#include "Engine.h"
using namespace std;
class car:public abstract_car
{
public:
    car();
    virtual void show_history();        ///汽车整体的历史
    virtual void show_argument(){}      ///后续用，在此声明为虚函数
    void show_passage();                ///关于汽车知识的文章
    virtual void show_picture();        ///展示汽车图片
    virtual ~car(){}
protected:
    Engine engine;          ///发动机参数
    string TM;              ///车牌
    string length,width,height;///长 宽 高
    string car_model;       ///车型
    string tire_num;        ///轮胎数目
    string seat_num;        ///座位数目
    string displacement;    ///排量
    string Fuel_consumption;///油耗
    string car_body_structure;///车体结构
};



