#include"bus.h"
using namespace std;
bus::bus(){}
void bus::show_argument(int p)
{
        /*system("\"c:\Program Files\Internet Explorer\iexplor.exe\"��ַ");*////ͨ������ie�����ʵ�֣�ֱ��չʾ��ҳ
        ///�ļ��Ĳ���
        /*ostringstream os;
        os<<"bus_\\bus_"<<p<<".txt";
        string s=os.str();
        ifstream file(s.c_str());
        while(file)
        {
            getline(file,s);
            cout<<s<<endl;
        }*/
        ///ͼƬ���ɹ���������
}
void bus::show_picture(string p,string q)
{
    car *c=this;
    c->show_picture(p,q);///����֮ǰ�ĺ���ʵ���ظ�ʹ��
}
void bus::show_history(int p)
{
        /*system("\"c:\Program Files\Internet Explorer\iexplor.exe\"��ַ");*////ͨ������ie�����ʵ�֣�ֱ��չʾ��ҳ
        ///�ļ�����
        /*ostringstream os;
        os<<"bus_\\bus_history_"<<p<<".txt";
        string s=os.str();
        ifstream file(s.c_str());
        while(file)
        {
            getline(file,s);
            cout<<s<<endl;
        }*/
        ///ͼƬ���ɹ���������
}
