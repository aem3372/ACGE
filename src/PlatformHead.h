#ifndef __ACGE_PLATFORM_DEFINE__
#define __ACGE_PLATFORM_DEFINE__

#ifdef WIN32
    #define _ACGE_PLATFORM_WIN32
	#include <windows.h>
#else
    #define _ACGE_PLATFORM_LINUX
#endif

#ifdef DLL_EXPORT
    #define ACGEAPI __declspec(dllexport)
#else
    #define ACGEAPI
#endif

#endif