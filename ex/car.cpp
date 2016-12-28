#include"car.h"
using namespace std;
car::car(){}
void car::show_history()
{
    /*system("\"c:\Program Files\Internet Explorer\iexplor.exe\"网址");*////通过调用ie浏览器实现，直接展示网页
        ifstream file(car_history.txt);
        while(file)
        {
            getline(file,s);
            cout<<s<<endl;
        }///通过文件实现，事先存好，直接打开
}
void car::show_passage()
{
    /*system("\"c:\Program Files\Internet Explorer\iexplor.exe\"网址");*////通过调用ie浏览器实现，直接展示网页
    ifstream file(car_passage.txt);
    while(file)
    {
        getline(file,s);
        cout<<s<<endl;
    }///通过文件实现，事先存好，直接打开
}
void car::show_picture(string p,string q)
{
    ostringstream os;
    os<<p<<q<<".JPG";
    string s=os.str();
    SDL_Init(SDL_INIT_EVERYTHING);
    IMG_Init(IMG_INIT_JPG);
    ///初始化两个母系统
    SDL_Surface* surf=IMG_Load(s.c_str());
    ///载入图片
    SDL_Window* wnd=SDL_CreateWindow("1",SDL_WINDOWPOS_CENTERED,SDL_WINDOWPOS_CENTERED,1024,768,SDL_WINDOW_SHOWN);
    ///创建窗口并定义大小且使其居中
    SDL_Renderer* rnd=SDL_CreateRenderer(wnd,-1,SDL_RENDERER_ACCELERATED|SDL_RENDERER_PRESENTVSYNC);
    ///索引，保持与屏幕相同的刷新率
    SDL_Texture* text=SDL_CreateTextureFromSurface(rnd,surf);
    ///弄到显存渲染
    SDL_RenderClear(rnd);
    ///清屏幕
    SDL_RenderCopy(rnd,text,NULL,NULL);
    ///在显存copy到屏幕预备下一帧上
    SDL_RenderPresent(rnd);
    ///显示
    SDL_Event e;
    ///事件
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
    ///事件是退出的时候 控制退出
    IMG_Quit();
    SDL_Quit();
}
