#include "PNGImage.h"

#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

void PNGImage::loadWithFile(const char* filename)
{
	image = FreeImage_Load(FIF_PNG, filename);
	if (!image)
		printf("load image failed!");
}

void PNGImage::saveToFile(const char* filename)
{
	FreeImage_Save(FIF_PNG, image, filename);
}

bool PNGImage::checkFormat(ImageFormat format)
{
	if (format == ImageFormat::IMAGE_FORMAT_PNG
			&& FreeImage_GetImageType(image) == FIF_PNG)
		return true;
	return false;
}

ImageUnitFormat PNGImage::getUnitFormat()
{
	if (image)
	{
		return ImageUnitFormat::IMAGE_UNIT_FORMAT_RGBA;
	}
	return ImageUnitFormat::IMAGE_UNIT_FORMAT_UNKNOW;
}

Size PNGImage::getSize()
{
	return Size{ FreeImage_GetWidth(image), FreeImage_GetHeight(image) };
}

int PNGImage::getWidth()
{
	return FreeImage_GetWidth(image);
}

int PNGImage::getHeight()
{
	return FreeImage_GetHeight(image);
}

void* PNGImage::getData()
{
	if (image)
	{
		return FreeImage_GetBits(image);
	}
	return nullptr;
}

int PNGImage::getDepth()
{
	if (image)
	{
		return FreeImage_GetBPP(image);
	}
	return -1;
}
