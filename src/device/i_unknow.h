#ifndef __ACGE_UNKNOW_INTERFACE__
#define __ACGE_UNKNOW_INTERFACE__

class IUnknow
{
public:
    virtual IUnknow* query(char* unknow) = 0;
    virtual void retain() = 0;
    virtual void release() = 0;
};

#endif