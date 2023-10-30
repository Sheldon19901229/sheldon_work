
#ifndef LOG_H
#define LOG_H

#include <stdarg.h>
#include <stdio.h>
#include <iostream>
constexpr unsigned int  TOOL_LOG_BUFF_SIZE = 1024;

void WriteLog(const char *msgInfo, ...) {
    if (msgInfo == nullptr) {
        return;
    }

    char logMsg[TOOL_LOG_BUFF_SIZE] = { 0 };
    va_list argList;
    va_start(argList,msgInfo);
    auto idx = vsnprintf(logMsg, sizeof(logMsg), msgInfo,argList);
    va_end(argList);

    if (idx < 0 || idx >= TOOL_LOG_BUFF_SIZE) {
        return;
    }

    logMsg[idx] = '\0';
    std::cout << logMsg;
}

#endif