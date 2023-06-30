
#ifndef TIMESTAMP_H
#define TIMESTAMP_H

#include <chrono>
#include <string>
#include <time.h>

enum TimeStampType {
    TIME_STAMP_NS = 0,
    TIME_STAMP_US,
    TIME_STAMP_MS,
    TIME_STAMP_S,
    TIME_STAMP_MIN,
    TIME_STAMP_H,
    TIME_STAMP_MAX
};

std::string GetMsTimeStamp();
uint64_t GetTimeCount(TimeStampType timeStampType);

#endif
