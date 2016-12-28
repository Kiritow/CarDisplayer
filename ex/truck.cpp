#include"truck.h"
using namespace std;
truck::truck(){}
void truck::show_argument(int p)
{
        /*system("\"c:\Program Files\Internet Explorer\iexplor.exe\"网址");*////通过调用ie浏览器实现，直接展示网页
        ostringstream os;
        os<<"truck_\\truck_"<<p<<".txt";
        string s=os.str();
        ifstream file(s.c_str());
        while(file)
        {
            getline(file,s);
            cout<<s<<endl;
        }
}
void truck::show_picture(string p,string q)
{
    car *c=this;
    c->show_picture(p,q);
}
void truck::show_history(int p)
{
        /*system("\"c:\Program Files\Internet Explorer\iexplor.exe\"网址");*////通过调用ie浏览器实现，直接展示网页
        ostringstream os;
        os<<"truck_\\truck_history_"<<p<<".txt";
        string s=os.str();
        ifstream file(s.c_str());
        while(file)
        {
            getline(file,s);
            cout<<s<<endl;
        }
}
