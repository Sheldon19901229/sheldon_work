
#ifndef TIMESTAMP_H
#define TIMESTAMP_H

#include <chrono>
#include <string>
#include <crtdefs.h>

enum TimeStampType {
    TIME_STAMP_NS = 0,
    TIME_STAMP_US,
    TIME_STAMP_MS,
    TIME_STAMP_S,
    TIME_STAMP_MIN,
    TIME_STAMP_H,
    TIME_STAMP_MAX
};

class CTimeStamp {
public:
    std::string GetMsTimeStamp();
    CTimeStamp() = default;
    ~CTimeStamp() = default;
    CTimeStamp(const CTimeStamp&) = delete;
    CTimeStamp(CTimeStamp&&) = delete;
    CTimeStamp& operator=(const CTimeStamp&) = delete;
    CTimeStamp& operator=(CTimeStamp&&) = delete;
private:
    uint32_t GetTimeCount(TimeStampType timeStampType);
private:
    time_t m_timeCount{ 0 };
};


#endif
