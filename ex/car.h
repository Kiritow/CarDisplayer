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
    virtual void show_history();        ///�����������ʷ
    virtual void show_argument(){}      ///�����ã��ڴ�����Ϊ�麯��
    void show_passage();                ///��������֪ʶ������
    virtual void show_picture();        ///չʾ����ͼƬ
    virtual ~car(){}
protected:
    Engine engine;          ///����������
    string TM;              ///����
    string length,width,height;///�� �� ��
    string car_model;       ///����
    string tire_num;        ///��̥��Ŀ
    string seat_num;        ///��λ��Ŀ
    string displacement;    ///����
    string Fuel_consumption;///�ͺ�
    string car_body_structure;///����ṹ
};



