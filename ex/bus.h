#include"car.h"
using namespace std;
class bus:public car
{
public:
    bus();
    void show_history();
    void show_picture();
    void show_argument();
    ~bus(){}
private:
    string zaikeshu;        ///载客数量
    string leixing;         ///商用等等，卧铺啥的
    string ranyouleixing;   ///燃油类型
    string shifoukongtiao;  ///空调？
    string xuangua;         ///悬挂
    string zhidongqi;       ///制动
};
