#pragma once
#include "config.h"
#include <functional>
using namespace std;

typedef int AnimationID;
#define INVALID_ANIMATIONID -1

/// forward declaration
class AnimationManager;

/// Stage
class Stage : public NonCopyable
{
private:
    Stage();
    ~Stage();
    struct impl;
    impl* pimpl;
    friend class AnimationManager;
public:
    int draw(SDL_Texture* text,int x,int y,int w,int h);
};

typedef function<int(Stage&,int)> AnimationCallback;
typedef pair<AnimationCallback,int> AnimationCallbackPack;

/// Animation Manager
class AnimationManager
{
public:
    AnimationManager();
    ~AnimationManager();
    void setRenderer(SDL_Renderer* rnd);
    AnimationID add(AnimationCallbackPack callbackpack);
protected:
    int play(AnimationID id,int frame,int LUx,int LUy,int RDx,int RDy);
    friend class PlayList;
private:
    struct impl;
    impl* pimpl;
};

extern AnimationManager animemanager;

class PlayList
{
public:
    PlayList();
    ~PlayList();
    int attachAnimationManager(AnimationManager* pAnimationManager);
    int addplay(AnimationID id,int LUx,int LUy,int RDx,int RDy);
    int addplay(function<int(SDL_Renderer* rnd)> rawPlayer);
    int playNext(int ClearScreen=1,int PresentScreen=1);
    void reset();
private:
    struct impl;
    impl* pimpl;
};
