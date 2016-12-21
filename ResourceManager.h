#include "config.h"

typedef int ResourceIndex;

struct res_pimpl;

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
    res_pimpl* pdata;

};

extern ResourceManager resmanager;
