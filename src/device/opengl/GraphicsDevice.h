#ifndef __ACGE_GRAPHICS_DEVICE_OPENGL_H__
#define __ACGE_GRAPHICS_DEVICE_OPENGL_H__

#include "../IGraphicsDevice.h"

#ifdef __cplusplus
extern "C" {
#endif 

ACGEAPI IGraphicsDevice* createInstance();
typedef IGraphicsDevice*(*CreateInstanceFun)();

#ifdef __cplusplus
}
#endif 

#endif
