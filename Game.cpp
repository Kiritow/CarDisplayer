#include "Game.h"
#include "ResourceManager.h"
#include "AnimationManager.h"
#include "EventManager.h"
#include "xbutton.h"

#define DEF_FPS 24

#define PNAME(pictureType,pictureID) _pic_##pictureType##_##pictureID
#define PIC(pictureType,pictureID) int PNAME(pictureType,pictureID)=-1;
#define PLOAD(pictureType,pictureID) PNAME(pictureType,pictureID)=resmanager.LoadPicture("img\\" #pictureType "\\" #pictureType "_" #pictureID ".png");
#define PLOADX(pictureType,pictureID) PNAME(pictureType,pictureID)=resmanager.LoadPicture("img\\" #pictureType "\\" #pictureType "_" #pictureID ".jpg");

#include "resources_list.hpp"

namespace Game
{
    int procInit(void* args)
    {
        int* pRunning=(int*)args;
        #include "resources_load.hpp"
        *pRunning=0;
        return 0;
    }
    void Init()
    {
        resmanager.LoadPicture("img\\loading\\loading_anim_01.png",1);
        resmanager.LoadPicture("img\\loading\\loading_anim_02.png",1);
        resmanager.LoadPicture("img\\loading\\loading_anim_03.png",1);
        resmanager.LoadPicture("img\\loading\\loading_anim_04.png",1);
        resmanager.LoadPicture("img\\loading\\loading_anim_05.png",1);
        resmanager.LoadPicture("img\\loading\\loading_anim_06.png",1);
        resmanager.LoadPicture("img\\loading\\loading_anim_07.png",1);
        resmanager.LoadPicture("img\\loading\\loading_anim_08.png",1);
        resmanager.LoadPicture("img\\loading\\loading_anim_09.png",1);
        resmanager.LoadPicture("img\\loading\\loading_anim_10.png",1);
        resmanager.LoadPicture("img\\loading\\loading_anim_11.png",1);
        resmanager.LoadPicture("img\\loading\\loading_anim_12.png",1);

        int _tw=resmanager.GetSize(0).w;
        int _th=resmanager.GetSize(0).h;

        AnimationCallback loadcallback=[&](Stage& stg,int frame)->int
        {
            stg.draw(resmanager.GetPicture(frame),0,0,_tw,_th);
            return 0;
        };
        animemanager.add(AnimationCallbackPack(loadcallback,12));

        PlayList ls;
        ls.addplay(0,WIN_WIDTH/2-_tw/2,WIN_HEIGHT/2-_th/2,0,0);
        ls.addplay([&](SDL_Renderer* rnd)->int{return 0;});

        EventManager em;
        int running=1;
        int need_update=1;

        SDL_Thread* td=SDL_CreateThread(procInit,"Init Thread",&running);

        while(ls.playNext()>=0&&running)
        {
            em.pollNext(running,need_update);
            SDL_Delay(1000/DEF_FPS);
        }

        int ret;
        SDL_WaitThread(td,&ret);
    }
    void Test()
    {
        EventManager evm;
        xbutton b;
        b.attachEventManager(evm);
        int running;
        int need_update;
        while(1)
        {
            if(evm.pollNext(running,need_update)>0);
            else SDL_Delay(1);
        }
    }
    void Main()
    {
        Test();
        Init();
    }
}
