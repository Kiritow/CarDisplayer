#include"car.h"
using namespace std;
car::car(){}
void car::show_history()
{
    /*system("\"c:\Program Files\Internet Explorer\iexplor.exe\"��ַ");*////ͨ������ie�����ʵ�֣�ֱ��չʾ��ҳ
        ifstream file(car_history.txt);
        while(file)
        {
            getline(file,s);
            cout<<s<<endl;
        }///ͨ���ļ�ʵ�֣����ȴ�ã�ֱ�Ӵ�
}
void car::show_passage()
{
    /*system("\"c:\Program Files\Internet Explorer\iexplor.exe\"��ַ");*////ͨ������ie�����ʵ�֣�ֱ��չʾ��ҳ
    ifstream file(car_passage.txt);
    while(file)
    {
        getline(file,s);
        cout<<s<<endl;
    }///ͨ���ļ�ʵ�֣����ȴ�ã�ֱ�Ӵ�
}
void car::show_picture(string p,string q)
{
    ostringstream os;
    os<<p<<q<<".JPG";
    string s=os.str();
    SDL_Init(SDL_INIT_EVERYTHING);
    IMG_Init(IMG_INIT_JPG);
    ///��ʼ������ĸϵͳ
    SDL_Surface* surf=IMG_Load(s.c_str());
    ///����ͼƬ
    SDL_Window* wnd=SDL_CreateWindow("1",SDL_WINDOWPOS_CENTERED,SDL_WINDOWPOS_CENTERED,1024,768,SDL_WINDOW_SHOWN);
    ///�������ڲ������С��ʹ�����
    SDL_Renderer* rnd=SDL_CreateRenderer(wnd,-1,SDL_RENDERER_ACCELERATED|SDL_RENDERER_PRESENTVSYNC);
    ///��������������Ļ��ͬ��ˢ����
    SDL_Texture* text=SDL_CreateTextureFromSurface(rnd,surf);
    ///Ū���Դ���Ⱦ
    SDL_RenderClear(rnd);
    ///����Ļ
    SDL_RenderCopy(rnd,text,NULL,NULL);
    ///���Դ�copy����ĻԤ����һ֡��
    SDL_RenderPresent(rnd);
    ///��ʾ
    SDL_Event e;
    ///�¼�
    int running=1;
    while(running)
    {
        while(SDL_PollEvent(&e))
        {
            if(e.type==SDL_QUIT)
            {
                running=0;
                break;
            }
        }
    }
    ///�¼����˳���ʱ�� �����˳�
    IMG_Quit();
    SDL_Quit();
}
