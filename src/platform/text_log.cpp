#include <cassert>
#include <cstdio>
#include "text_log.h"

class TextLog::TextLogPrivate
{
public:
	FILE* warningLog;
	FILE* infoLog;
	FILE* errorLog;
	FILE* debugLog;

	const char* warningPath;
	const char* infoPath;
	const char* errorPath;
	const char* debugPath;

	bool allFlag;

	TextLogPrivate()
	: warningLog(NULL)
	, infoLog(NULL)
	, errorLog(NULL)
	, debugLog(NULL)
	, warningPath(NULL)
	, infoPath(NULL)
	, errorPath(NULL)
	, debugPath(NULL)
	, allFlag(false)
	{

	}

	~TextLogPrivate()
	{
		if(warningLog)
		{
			fclose(warningLog);
		}
		if(infoLog)
		{
			fclose(infoLog);
		}
		if(errorLog)
		{
			fclose(errorLog);
		}
		if(debugLog)
		{
			fclose(debugLog);
		}
	}

	void startLog()
	{
		if(warningPath)
			warningLog = fopen(warningPath, "a+");
		if(infoPath)
			infoLog = fopen(infoPath, "a+");
		if(errorPath)
			errorLog = fopen(errorPath, "a+");
		if(debugPath)
			debugLog = fopen(debugPath, "a+");
		allFlag = true;
	}

	void stopLog()
	{
		if(warningLog)
		{
			fclose(warningLog);
			warningLog = NULL;
		}
		if(infoLog)
		{
			fclose(infoLog);
			infoLog = NULL;
		}
		if(errorLog)
		{
			fclose(errorLog);
			errorLog = NULL;
		}
		if(debugLog)
		{
			fclose(debugLog);
			debugLog = NULL;
		}
		allFlag = false;
	}
};

TextLog::TextLogPrivate* TextLog::impl = new TextLog::TextLogPrivate();

void TextLog::startLog(const TextLogStruct& setting)
{
	impl->warningPath = setting.warningPath;
	impl->infoPath = setting.infoPath;
	impl->errorPath = setting.errorPath;
	impl->debugPath = setting.debugPath;

	impl->startLog();
}

void TextLog::stopLog()
{
	impl->stopLog();
}

void TextLog::warning(int tag, const char* i)
{
	if(impl->allFlag && impl->warningLog)
		fprintf(impl->warningLog, "%d:%s\n", tag, i);
}

void TextLog::info(int tag, const char* i)
{
	if(impl->allFlag && impl->infoLog)
		fprintf(impl->infoLog, "%d:%s\n", tag, i);	
}

void TextLog::error(int tag, const char* i)
{
	if(impl->allFlag && impl->errorLog)
		fprintf(impl->errorLog, "%d:%s\n", tag, i);
}

void TextLog::debug(int tag, const char* i)
{
	if(impl->allFlag && impl->debugLog)
		fprintf(impl->debugLog, "%d:%s\n", tag, i);
}
