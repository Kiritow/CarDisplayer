#include"SUV.h"
using namespace std;
SUV::SUV(){}
void SUV::show_argument(int p)
{
        /*system("\"c:\Program Files\Internet Explorer\iexplor.exe\"��ַ");*////ͨ������ie�����ʵ�֣�ֱ��չʾ��ҳ
        ostringstream os;
        os<<"SUV_\\SUV_"<<p<<".txt";
        string s=os.str();
        ifstream file(s.c_str());
        while(file)
        {
            getline(file,s);
            cout<<s<<endl;
        }
}
void SUV::show_picture(string p,string q)
{
    car *c=this;
    c->show_picture(p,q);
}
void SUV::show_history(int p)
{
        /*system("\"c:\Program Files\Internet Explorer\iexplor.exe\"��ַ");*////ͨ������ie�����ʵ�֣�ֱ��չʾ��ҳ
        ostringstream os;
        os<<"SUV_\\SUV_history_"<<p<<".txt";
        string s=os.str();
        ifstream file(s.c_str());
        while(file)
        {
            getline(file,s);
            cout<<s<<endl;
        }
}
