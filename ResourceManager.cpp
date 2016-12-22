#include "ResourceManager.h"
#include <vector>
#include <map>
#include <string>
using namespace std;


struct vdpack
{
    SDL_Texture* text;
    string name;
    int isvalid;
    int inuse;
    int w,h;
};

struct ResourceManager::res_pimpl
{
    vector<vdpack> vec;
    map<int,bool> gmap;
};

ResourceManager::ResourceManager()
{
    pdata=new res_pimpl;
}

ResourceManager::~ResourceManager()
{
    delete pdata;
}

ResourceIndex ResourceManager::LoadPicture(const char* filename,int must_in_mem)
{
    printf("ResourceManager::LoadPicture : Loading %s\n",filename);
    SDL_Texture* text=IMG_LoadTexture(rnd,filename);
    if(text==NULL)
    {
        /// Try Again.
        TryFreeMemory();
        text=IMG_LoadTexture(rnd,filename);
        if(text==NULL)
        {
            thread_local char errMsg[1024];
            memset(errMsg,0,1024);
            strcpy(errMsg,SDL_GetError());
            printf("ResourceManager::LoadPicture : Failed Recursively : %s\n",errMsg);
            /// If Error is "Out of memory" then store it in Vector, but don't push it into GMAP.
            /// We can call this "Cache of Infos"
            if(strstr(errMsg,"Out of memory")!=NULL)
            {
                /// Low Memory is the cause.
                vdpack notgoodpack;
                notgoodpack.text=NULL;
                notgoodpack.w=0;
                notgoodpack.h=0;
                notgoodpack.name=filename;
                notgoodpack.isvalid=0;
                notgoodpack.inuse=0;
                pdata->vec.push_back(notgoodpack);

                printf("ResourceManager::LoadPicture : Info Stored. (Not Fully Loaded) (%d)\n",pdata->vec.size()-1);
                return pdata->vec.size()-1;
            }
            else
            {
                /// Other Thing Cause This.
                printf("ResourceManager::LoadPicture : Fatal Failure.\n");
                return -1;
            }
        }
    }

    vdpack thispack;
    thispack.text=text;
    SDL_QueryTexture(text,NULL,NULL,&thispack.w,&thispack.h);
    thispack.name=filename;
    thispack.isvalid=1;
    thispack.inuse=0;
    pdata->vec.push_back(thispack);
    /// Push this new texture into GMAP.
    pdata->gmap[pdata->vec.size()-1]=1;

    printf("ResourceManager::LoadPicture : Loaded (%d)\n",pdata->vec.size()-1);
    return pdata->vec.size()-1;
}

SDL_Rect ResourceManager::GetSize(ResourceIndex idx)
{
    SDL_Rect rect;
    rect.w=pdata->vec.at(idx).w;
    rect.h=pdata->vec.at(idx).h;
    return rect;
}

void ResourceManager::TryFreeMemory()
{
    printf("ResourceManager::TryFreeMemory Called.\n");
    int cc=0;
    for(auto iter=pdata->gmap.begin();iter!=pdata->gmap.end();)
    {
        if(pdata->vec.at(iter->first).inuse==0)
        {
            printf("ResourceManager::TryFreeMemory : ResourceIndex(%d) Freed.\n",iter->first);
            pdata->vec.at(iter->first).isvalid=0;
            SDL_DestroyTexture(pdata->vec.at(iter->first).text);
            pdata->gmap.erase(iter);
            ++cc;

            iter=pdata->gmap.begin();
        }
        else
        {
            ++iter;
        }
    }
    printf("ResourceManager::TryFreeMemory : %d texture freed.\n",cc);
}

int ResourceManager::RequestLoadPicture(ResourceIndex idx)
{
    if(idx<0) return -1;
    if(pdata->vec.at(idx).isvalid) return 0;

    SDL_Texture* text=IMG_LoadTexture(rnd,pdata->vec.at(idx).name.c_str());
    if(text==NULL)
    {
        TryFreeMemory();
        text=IMG_LoadTexture(rnd,pdata->vec.at(idx).name.c_str());
        if(text==NULL)
        {
            printf("ResourceManager::RequestLoadPicture Failed: %s\n",SDL_GetError());
            return -1;/// Failed to Load Picture.
        }
    }

    pdata->vec.at(idx).text=text;
    pdata->vec.at(idx).isvalid=1;
    SDL_QueryTexture(text,NULL,NULL,&pdata->vec.at(idx).w,&pdata->vec.at(idx).h);
    return 0;
}

SDL_Texture* ResourceManager::GetPicture(ResourceIndex idx)
{
    if(idx<0) return NULL;
    if(pdata->vec.at(idx).isvalid)
    {
        if(pdata->vec.at(idx).inuse==0)
        {
            pdata->gmap[idx]=1;
            pdata->vec.at(idx).inuse=1;
        }
        return pdata->vec.at(idx).text;
    }
    else
    {
        if(RequestLoadPicture(idx)<0)
        {
            pdata->vec.at(idx).inuse=0;
            return NULL;
        }
        else
        {
            pdata->vec.at(idx).inuse=1;
            return pdata->vec.at(idx).text;
        }
    }
}

void ResourceManager::NotInUse(ResourceIndex idx)
{
    if(idx<0) return ;
    pdata->vec.at(idx).inuse=0;
}

ResourceManager resmanager;


struct resptr::impl
{
    ResourceManager* pres;
    ResourceIndex idx;
    SDL_Texture* text;
};

resptr::resptr(ResourceIndex index,ResourceManager* pResManager_in)
{
    pimpl=new impl;
    pimpl->pres=pResManager_in;
    pimpl->idx=index;
    pimpl->text=pimpl->pres->GetPicture(pimpl->idx);
}

resptr::operator SDL_Texture*()
{
    return pimpl->text;
}

resptr::~resptr()
{
    pimpl->pres->NotInUse(pimpl->idx);
    delete pimpl;
}
