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
    string wheel_base;  ///��ࣨ����ǰ�������ľ��룺�����˿Ϳռ��С��
    string wheel_track; ///�־ࣨ������ǰ��/����֮����룩
    string Luggage;     ///������ݻ��������������������
    string turning_diameter;///��Сת��ֱ��
    string dipangaodu;  ///���̸߶�
    string maximum_gradability;///������¶�
    string jiao;        ///�ӽ��ǣ�ͨ���ǣ���ȥ��
};
