#include "../i_graphics_device.h"
#include "../i_graphics_drawpoint.h"

class GraphiceDevice
: public IDrawPoint
, public IGraphicsDevice
{
public:
    graphiceDevice();
    ~graphiceDevice();

    virtual bool query(char* unknow);
    virtual void drawPoint(int x, int y);
};
