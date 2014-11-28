#ifndef __ACGE_GRAPHICS_CLEARSUFFACE_INTERFACE__
#define __ACGE_GRAPHICS_CLEARSUFFACE_INTERFACE__

#include "i_unknow.h"

class IClearSufface
: public IUnknow
{
public:
    virtual void clearSufface() = 0;
};

#endif