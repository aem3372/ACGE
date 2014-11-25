#ifndef __ACGE_UNKNOW_INTERFACE__
#define __ACGE_UNKNOW_INTERFACE__

class IUnknow
{
public:
    virtual int queryInterface(char* unknow, void** pp) = 0;
    virtual void retain() = 0;
    virtual void release() = 0;
};

#endif