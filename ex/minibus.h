#include"car.h"
using namespace std;
class minibus:public car
{
public:
    minibus();
    void show_history();
    void show_picture();
    void show_argument();
    ~minibus(){};
private:
    string price;   ///�۸�
    string ranyouleixing;   ///ȼ������
    string youhao;     ///�ͺ�
    string pailiang;   ///����
    string biansuxiang;///������
    string qudongfangshi;///������ʽ
    string zhengbeizhiliang;///��������
    string zuidagonglv;///�����
};
