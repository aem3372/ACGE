#include <cstdio>
#include <cstdlib>
#include "platform/text_log.h"

int main() 
{
    TextLogStruct setting;
    setting.warningPath = "warning.log";
    setting.infoPath = "info.log";
    setting.errorPath = "error.log";
    setting.debugPath = "debug.log";

    TextLog::startLog(setting);
    TextLog::warning(0, "warning");
    TextLog::info(0, "info");
    TextLog::error(0, "error");
    TextLog::debug(0, "debug");
    TextLog::stopLog();
    
    TextLog::warning(0, "warning");
    TextLog::info(0, "info");
    TextLog::error(0, "error");
    TextLog::debug(0, "debug");
    return 0;
}