#include"pick_up.h"
using namespace std;
pick_up::pick_up(){}
void pick_up::show_argument(int p)
{
        /*system("\"c:\Program Files\Internet Explorer\iexplor.exe\"��ַ");*////ͨ������ie�����ʵ�֣�ֱ��չʾ��ҳ
        ostringstream os;
        os<<"pick_up_\\pick_up_"<<p<<".txt";
        string s=os.str();
        ifstream file(s.c_str());
        while(file)
        {
            getline(file,s);
            cout<<s<<endl;
        }
}
void pick_up::show_picture(string p,string q)
{
    car *c=this;
    c->show_picture(p,q);
}
void pick_up::show_history(int p)
{
        /*system("\"c:\Program Files\Internet Explorer\iexplor.exe\"��ַ");*////ͨ������ie�����ʵ�֣�ֱ��չʾ��ҳ
        ostringstream os;
        os<<"pick_up_\\pick_up_history_"<<p<<".txt";
        string s=os.str();
        ifstream file(s.c_str());
        while(file)
        {
            getline(file,s);
            cout<<s<<endl;
        }
}
