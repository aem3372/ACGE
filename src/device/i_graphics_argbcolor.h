#ifndef __ACGE_GRAPHICS_ARGBCOLOR_INTERFACE__
#define __ACGE_GRAPHICS_ARGBCOLOR_INTERFACE__

#include "i_unknow.h"

class IARGBColor
: public IUnknow
{
public:
    virtual void setARGBColor(unsigned long argb) = 0;
    virtual unsigned long getARGBColor() = 0;
};

#endif