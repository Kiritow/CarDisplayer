#include "car.h"
using namespace std;
class SUV:public car
{
public:
    SUV();
    void show_history();
    void show_picture();
    void show_argument();
    ~SUV(){}
private:
    string wheel_base;  ///轴距（车辆前后轮中心距离：决定乘客空间大小）
    string wheel_track; ///轮距（车辆两前轮/后轮之间距离）
    string Luggage;     ///行李舱容积（行李箱的载物能力）
    string turning_diameter;///最小转弯直径
    string dipangaodu;  ///底盘高度
    string maximum_gradability;///最大爬坡度
    string jiao;        ///接近角，通过角，离去角
};
