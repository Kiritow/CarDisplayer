#pragma once
#include "car.h"
using namespace std;
class automobile:virtual public car   ///С�γ�
{
public:
    automobile();
    void show_history(int p);
    void show_picture(int p);
    void show_argument(int p);
    void show_game();///use in game
    ~automobile(){}
protected:
    string TM;          ///����
    string wheel_base;  ///��ࣨ����ǰ�������ľ��룺�����˿Ϳռ��С��
    string wheel_track; ///�־ࣨ������ǰ��/����֮����룩
    string Luggage;     ///������ݻ��������������������
    string turning_diameter;///��Сת��ֱ��
    string max_speed;   ///����ٶ�
    string biansuxiang; ///������
};
