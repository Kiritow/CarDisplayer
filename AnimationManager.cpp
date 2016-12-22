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
