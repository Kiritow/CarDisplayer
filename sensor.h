#include "config.h"

class sensor
{
public:
    sensor(int LUx,int LUy,int RDx,int RDy);
    ~sensor();
    bool inrange(int x,int y);
    void setMiddle(int* px,int* py);
    void setMiddle(int& val_x,int& val_y);
private:
    struct impl;
    impl* pimpl;
};
