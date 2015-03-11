#ifndef __ACGE_PLATFORM_DYNAMIC_LINKER__
#define __ACGE_PLATFORM_DYNAMIC_LINKER__

#include "platform/platform_head.h"

class DynamicLinker
{
public:
	static DynamicLinker* getInstance();
	bool loadLibrary(const char* name, const char* path);
    bool freeLibrary(const char* name);
    void* getProcAddress(const char* name, const char* procName);
private:
	DynamicLinker();
	~DynamicLinker();
	static DynamicLinker* instance;
	class DynamicLinkerPrivate;
	DynamicLinkerPrivate* impl;
};

#endif
