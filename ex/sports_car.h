#include "car.h"
using namespace std;
class sports_car:public car
{
public:
    sports_car();
    void show_history();
    void show_picture();
    void show_argument();
    ~sports_car(){}
private:
    string kerb_weight;///整备质量
    string torque;     ///扭矩
    string horsepower; ///马力
    string f0_100;     ///百公里加速
    string transmission_system;///传动系统
    string max_speed;  ///最高时速
    string cylinder;   ///气缸
    string price;      ///价格
};
