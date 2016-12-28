#include "AnimationManager.h"
#include <vector>
#include <algorithm>
using namespace std;

struct Stage::impl
{
    int LUx,LUy;
    int RDx,RDy;
    SDL_Renderer* rnd;
};

Stage::Stage()
{
    pimpl=new impl;
}

Stage::~Stage()
{
    delete pimpl;
}

int Stage::draw(SDL_Texture* text,int x,int y,int w,int h)
{
    SDL_Rect rect;
    rect.x=x+pimpl->LUx;
    rect.y=y+pimpl->LUy;
    rect.w=w;
    rect.h=h;
    return SDL_RenderCopy(pimpl->rnd,text,NULL,&rect);
}


struct AnimationManager::impl
{
    vector<AnimationCallbackPack> vec;
    SDL_Renderer* sysrnd;
};

AnimationManager::AnimationManager()
{
    pimpl=new impl;
}

AnimationManager::~AnimationManager()
{
    delete pimpl;
}

void AnimationManager::setRenderer(SDL_Renderer* rnd)
{
    pimpl->sysrnd=rnd;
}

AnimationID AnimationManager::add(AnimationCallbackPack              callbackpack)
{
    pimpl->vec.push_back(callbackpack);
    return pimpl->vec.size()-1;
}

int AnimationManager::play(AnimationID id,int frame,int LUx,int LUy,int RDx,int RDy)
{
    if(id<0) return -1;

    Stage s;
    s.pimpl->LUx=LUx;
    s.pimpl->LUy=LUy;
    s.pimpl->RDx=RDx;
    s.pimpl->RDy=RDy;
    s.pimpl->rnd=pimpl->sysrnd;
    pimpl->vec.at(id).first(s,frame);
    return 0;
}

AnimationManager animemanager;

struct PlayList::impl
{
    AnimationManager* pManager;
    SDL_Renderer* rnd;
    vector<int> realList;
    vector<function<int(SDL_Renderer* rnd)>> rawvec;
    vector<tuple<AnimationID,int,int,int,int,int,int>> animevec;
};

PlayList::PlayList()
{
    pimpl=new impl;
    attachAnimationManager(&animemanager);
}
PlayList::~PlayList()
{
    delete pimpl;
}
int PlayList::attachAnimationManager(AnimationManager* pAnimationManager)
{
    if(!pAnimationManager) return -1;
    pimpl->pManager=pAnimationManager;
    pimpl->rnd=pAnimationManager->pimpl->sysrnd;
    return 0;
}
int PlayList::addplay(AnimationID id,int LUx,int LUy,int RDx,int RDy)
{
    if(!pimpl->rnd) return -1;

    pimpl->animevec.push_back(make_tuple(id,0,pimpl->pManager->pimpl->vec.at(id).second,LUx,LUy,RDx,RDy));
    int resid=pimpl->animevec.size()-1;
    resid=(1<<16)|resid;
    pimpl->realList.push_back(resid);
    return 0;
}
int PlayList::addplay(function<int(SDL_Renderer* rnd)> rawPlayer)
{
    if(!pimpl->rnd) return -1;

    pimpl->rawvec.push_back(rawPlayer);
    int resid=pimpl->animevec.size()-1;
    pimpl->realList.push_back(resid);
    return 0;
}
int PlayList::playNext(int ClearScreen,int PresentScreen)
{
    int ret=0;
    if(ClearScreen) SDL_RenderClear(pimpl->rnd);
    for(auto residx:pimpl->realList)
    {
        if(residx>>16)
        {
            auto& tup=pimpl->animevec.at(residx & ((1<<16)-1));
            if(get<1>(tup) >= get<2>(tup))
            {
                get<1>(tup)=0;
            }
            ret&=pimpl->pManager->play(get<0>(tup),get<1>(tup),get<3>(tup),get<4>(tup),get<5>(tup),get<6>(tup));
            ++get<1>(tup);
        }
        else
        {
            ret&=pimpl->rawvec.at(residx)(pimpl->rnd);
        }
    }
    if(PresentScreen) SDL_RenderPresent(pimpl->rnd);

    return ret;
}

void ShowPictureVec(vector<SDL_Texture*> vec)
{
    int maxy=0;

    vector<pair<int,int>> info;
    for(auto& x:vec)
    {
        int w,h;
        SDL_QueryTexture(x,NULL,NULL,&w,&h);
        info.push_back(pair<int,int>(w,h));
        maxy+=h;
    }

    maxy-=WIN_HEIGHT;

    int sz=info.size();

    int cy=0;

    int running=1;
    SDL_Event e;
    int update=1;

    while(running)
    {
        while(!update&&SDL_WaitEvent(&e))
        {
            switch(e.type)
            {
            case SDL_QUIT:
                update=1;
                running=0;
                break;
            case SDL_MOUSEWHEEL:
                {
                    update=1;
                    switch(e.wheel.y<0)
                    {
                    case 0:
                        cy=cy-WIN_WIDTH/3*2;
                        cy=max(cy,0);
                        break;
                    case 1:
                        cy=cy+WIN_WIDTH/3*2;
                        cy=min(cy,maxy);
                        break;
                    }
                }
            case SDL_KEYDOWN:
                {
                    if(e.key.keysym.sym==SDLK_ESCAPE)
                    {
                        running=0;
                        update=1;
                    }
                }
                break;
            }
        }

        SDL_RenderClear(rnd);
        int tny=0;
        for(int i=0;i<sz;i++)
        {
            if(tny<=cy)
            {
                printf("%d %d\n",tny+info.at(i).second,cy+WIN_HEIGHT);

                if(tny+info.at(i).second>=cy+WIN_HEIGHT)
                {
                    /// ONLY 1 Picture
                    SDL_Rect rect;
                    rect.x=390;
                    rect.w=1530-390;
                    rect.h=WIN_HEIGHT;
                    rect.y=cy-tny;
                    SDL_RenderCopy(rnd,vec.at(i),&rect,NULL);
                    break;
                }
                else
                {
                    /// Upper Half of Screen
                    SDL_Rect rect;
                    rect.x=390;
                    rect.w=1530-390;
                    rect.h=info.at(i).second-(cy-tny);
                    rect.y=cy-tny;

                    SDL_Rect dest;
                    dest.x=0;
                    dest.y=0;
                    dest.w=WIN_WIDTH;
                    dest.h=rect.h;

                    SDL_RenderCopy(rnd,vec.at(i),&rect,&dest);

                    rect.x=390;
                    rect.w=1530-390;
                    rect.h=WIN_HEIGHT-(info.at(i).second-(cy-tny));
                    rect.y=0;

                    dest.x=0;
                    dest.y=info.at(i).second-(cy-tny);
                    dest.w=WIN_WIDTH;
                    dest.h=WIN_HEIGHT-(info.at(i).second-(cy-tny));

                    SDL_RenderCopy(rnd,vec.at(i+1),&rect,&dest);
                    break;
                }
            }

            tny+=info.at(i).second;
        }
        SDL_RenderPresent(rnd);

        update=0;
    }
}
