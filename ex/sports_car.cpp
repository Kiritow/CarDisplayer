#include"sports_car.h"
using namespace std;
sports_car::sports_car(){}
void sports_car::show_argument(int p)
{
        /*system("\"c:\Program Files\Internet Explorer\iexplor.exe\"网址");*////通过调用ie浏览器实现，直接展示网页
        ostringstream os;
        os<<"sports_car_\\sports_car_"<<p<<".txt";
        string s=os.str();
        ifstream file(s.c_str());
        while(file)
        {
            getline(file,s);
            cout<<s<<endl;
        }
}
void sports_car::show_picture(string p,string q)
{
    car *c=this;
    c->show_picture(p,q);
}
void sports_car::show_history(int p)
{
        /*system("\"c:\Program Files\Internet Explorer\iexplor.exe\"网址");*////通过调用ie浏览器实现，直接展示网页
        ostringstream os;
        os<<"sports_car_\\sports_car_history_"<<p<<".txt";
        string s=os.str();
        ifstream file(s.c_str());
        while(file)
        {
            getline(file,s);
            cout<<s<<endl;
        }
}
