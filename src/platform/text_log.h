#ifndef __ACGE_PLATFORM_TEXTLOG__
#define __ACGE_PLATFORM_TEXTLOG__

#include "platform/platform_head.h"

struct TextLogStruct 
{
	const char* warningPath;
	const char* infoPath;
	const char* errorPath;
	const char* debugPath;
};

class TextLog
{
public:
	static void startLog(const TextLogStruct& setting);
	static void warning(int tag, const char* i);
	static void info(int tag, const char* i);
	static void error(int tag, const char* i);
	static void debug(int tag, const char* i);
	static void stopLog();
private:
	TextLog();
	class TextLogPrivate;
	static TextLogPrivate* impl;
};

#endif
