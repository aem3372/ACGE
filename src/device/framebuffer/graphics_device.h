#include <linux/fb.h>
#include "../i_graphics_device.h"
#include "../i_graphics_drawpoint.h"
#include "../i_graphics_argbcolor.h"
#include "../graphics_device_struct.h"

class GraphicsDevice
: public IDrawPoint
, public IARGBColor
, public IGraphicsDevice
{
public:
    GraphicsDevice();
    ~GraphicsDevice();

    virtual void retain();
    virtual void release();
    virtual int queryInterface(char* unknow, void** pp);
    virtual void drawPoint(int x, int y);
    virtual void setARGBColor(unsigned long argb);
    virtual unsigned long getARGBColor();
    virtual GraphicsDeviceInfo getDeviceInfo();
    
private:
    int reference;
    int fp;
    char* fbp;
    struct fb_var_screeninfo vinfo;
    struct fb_fix_screeninfo finfo;
    int screensize;
    unsigned long color;
};
