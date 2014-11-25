#include "i_unknow.h"

class IARGBColor
: public IUnknow
{
    virtual void setARGBColor(unsigned long argb) = 0;
    virtual unsigned long getARGBColor() = 0;
};