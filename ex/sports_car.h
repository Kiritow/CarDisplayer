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
    string kerb_weight;///��������
    string torque;     ///Ť��
    string horsepower; ///����
    string f0_100;     ///�ٹ������
    string transmission_system;///����ϵͳ
    string max_speed;  ///���ʱ��
    string cylinder;   ///����
    string price;      ///�۸�
};
