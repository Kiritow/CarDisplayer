#pragma once
#include "config.h"

typedef int ResourceIndex;



class ResourceManager
{
public:
    ResourceManager();
    ~ResourceManager();
    ResourceIndex LoadPicture(const char* filename,int must_in_mem=0);
    SDL_Texture* GetPicture(ResourceIndex idx);
    void NotInUse(ResourceIndex idx);
    SDL_Rect GetSize(ResourceIndex idx);
private:
    int RequestLoadPicture(ResourceIndex idx);
    void TryFreeMemory();
private:
    struct res_pimpl;
    res_pimpl* pdata;

};

extern ResourceManager resmanager;

class resptr
{
public:
    resptr(ResourceIndex index,ResourceManager* pResManager_in=&resmanager);
    void load();
    void unload();
    ~resptr();
    operator SDL_Texture* ();
private:
    struct impl;
    impl* pimpl;
};
