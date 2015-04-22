#ifndef __ACGE_TOOLS_PNG_IMAGE__
#define __ACGE_TOOLS_PNG_IMAGE__

#include "Image.h"
#include "FreeImage.h"

class PNGImage
: public Image
{
public:
	virtual void loadWithFile(const char* filename) override;
	virtual void saveToFile(const char* filename) override;
	virtual bool checkFormat(ImageFormat format) override;
	virtual int getWidth() override;
	virtual int getHeight() override;
	virtual ImageUnitFormat getUnitFormat() override;
	virtual Size getSize() override;
	virtual void* getData() override;
	virtual int getDepth() override;
private:
	FIBITMAP* image;
};

#endif