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
    string ranyouleixing;   ///ȼ������
    string luntaileixing;   ///��̥����
    string leixing;         ///������
    string zaizhongliang;   ///������
    string zhoushu;         ///������
    string kezhuangzaiwu;   ///װ����Ʒ
    string zhidongqi;       ///�ƶ�
};
