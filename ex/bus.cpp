#include"bus.h"
using namespace std;
bus::bus(){}
void bus::show_argument(int p)
{
        /*system("\"c:\Program Files\Internet Explorer\iexplor.exe\"网址");*////通过调用ie浏览器实现，直接展示网页
        ///文件的操作
        /*ostringstream os;
        os<<"bus_\\bus_"<<p<<".txt";
        string s=os.str();
        ifstream file(s.c_str());
        while(file)
        {
            getline(file,s);
            cout<<s<<endl;
        }*/
        ///图片（可滚动）操作
}
void bus::show_picture(string p,string q)
{
    car *c=this;
    c->show_picture(p,q);///调用之前的函数实现重复使用
}
void bus::show_history(int p)
{
        /*system("\"c:\Program Files\Internet Explorer\iexplor.exe\"网址");*////通过调用ie浏览器实现，直接展示网页
        ///文件操作
        /*ostringstream os;
        os<<"bus_\\bus_history_"<<p<<".txt";
        string s=os.str();
        ifstream file(s.c_str());
        while(file)
        {
            getline(file,s);
            cout<<s<<endl;
        }*/
        ///图片（可滚动）操作
}
