#ifndef __ACGE_GRAPHICS_DEVICE_FACTORY__
#define __ACGE_GRAPHICS_DEVICE_FACTORY__

#include "i_graphics_device.h"
#include <map>
#include <string>
#include <fstream>
#include <sstream>

class GraphicsDeviceFactory
{
public:
    static GraphicsDeviceFactory* getInstance();
    IGraphicsDevice* createByName(const char* name);
private:
    GraphicsDeviceFactory();
    ~GraphicsDeviceFactory();
    static GraphicsDeviceFactory* instance;
private:
    void loadList();
};

#endif