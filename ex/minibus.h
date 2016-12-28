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
    string price;   ///价格
    string ranyouleixing;   ///燃油类型
    string youhao;     ///油耗
    string pailiang;   ///排量
    string biansuxiang;///变速箱
    string qudongfangshi;///驱动方式
    string zhengbeizhiliang;///整备质量
    string zuidagonglv;///最大功率
};
