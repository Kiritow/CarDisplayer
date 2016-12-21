#include "Game.h"
#include "ResourceManager.h"
#include "AnimationManager.h"

namespace Game
{
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
        ls.attachAnimationManager(&animemanager);
        ls.addplay(0,WIN_WIDTH/2-_tw/2,WIN_HEIGHT/2-_th/2,0,0);
        while(ls.playNext()>=0)
        {
            SDL_PollEvent(NULL);
        }
    }
    void Main()
    {
        Init();
    }
}
