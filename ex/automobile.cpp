#include"automobile.h"
using namespace std;
automobile::automobile(){}
void automobile::show_argument(int p)
{
        /*system("\"c:\Program Files\Internet Explorer\iexplor.exe\"��ַ");*////ͨ������ie�����ʵ�֣�ֱ��չʾ��ҳ
        ostringstream os;
        os<<"automobile_\\automobile_"<<p<<".txt";
        string s=os.str();
        ifstream file(s.c_str());
        while(file)
        {
            getline(file,s);
            cout<<s<<endl;
        }
}
void automobile::show_picture(string p,string q)
{
    car *c=this;
    c->show_picture(p,q);
}
void automobile::show_history(int p)
{
        /*system("\"c:\Program Files\Internet Explorer\iexplor.exe\"��ַ");*////ͨ������ie�����ʵ�֣�ֱ��չʾ��ҳ
        ostringstream os;
        os<<"automobile_\\automobile_history_"<<p<<".txt";
        string s=os.str();
        ifstream file(s.c_str());
        while(file)
        {
            getline(file,s);
            cout<<s<<endl;
        }
}
