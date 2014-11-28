#ifndef __ACGE_GRAPHICS_DRAWPOINT_INTERFACE__
#define __ACGE_GRAPHICS_DRAWPOINT_INTERFACE__

class IDrawPoint
: public IUnknow
{
public:
    virtual void drawPoint(int x, int y) = 0;
};

#endif