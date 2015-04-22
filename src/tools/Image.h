#ifndef __ACGE_TOOLS_IMAGE__
#define __ACGE_TOOLS_IMAGE__

#include "base/BaseStruct.h"

enum class ImageFormat{
	IMAGE_FORMAT_UNKNOW,
	IMAGE_FORMAT_BMP,
	IMAGE_FORMAT_PNG
};

enum class ImageUnitFormat{
	IMAGE_UNIT_FORMAT_UNKNOW,
	IMAGE_UNIT_FORMAT_RGBA,
	IMAGE_UNIT_FORMAT_ARGB,
	IMAGE_UNIT_FORMAT_RGB
};

class Image{
public:
	virtual void loadWithFile(const char* filename) = 0;
	virtual void saveToFile(const char* filename) = 0;
	virtual bool checkFormat(ImageFormat format) = 0;
	virtual int getWidth() = 0;
	virtual int getHeight() = 0;
	virtual ImageUnitFormat getUnitFormat() = 0;
	virtual Size getSize() = 0;
	virtual void* getData() = 0;
	virtual int getDepth() = 0;
};

#endif
