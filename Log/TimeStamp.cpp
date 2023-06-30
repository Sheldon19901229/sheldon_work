#include "TimeStamp.h"
#include <iostream>

namespace {
    constexpr time_t XR_ZONE_TIME_MS_RATIO_E8 = 8 * 60 * 60 * 1000;
};

uint64_t GetTimeCount(TimeStampType timeStampType)
{
    switch (timeStampType) {
        case TIME_STAMP_NS: {
            std::chrono::time_point<std::chrono::system_clock, std::chrono::nanoseconds> timePoint = std::chrono::time_point_cast<std::chrono::nanoseconds>(std::chrono::system_clock::now());
            auto tmp = std::chrono::duration_cast<std::chrono::nanoseconds>(timePoint.time_since_epoch());
            return tmp.count();
        }
        case TIME_STAMP_US: {
            std::chrono::time_point<std::chrono::system_clock, std::chrono::microseconds> timePoint = std::chrono::time_point_cast<std::chrono::microseconds>(std::chrono::system_clock::now());
            auto tmp = std::chrono::duration_cast<std::chrono::microseconds>(timePoint.time_since_epoch());
            return tmp.count();
        }
        case TIME_STAMP_MS: {
            std::chrono::time_point<std::chrono::system_clock, std::chrono::milliseconds> timePoint = std::chrono::time_point_cast<std::chrono::milliseconds>(std::chrono::system_clock::now());
            auto tmp = std::chrono::duration_cast<std::chrono::milliseconds>(timePoint.time_since_epoch());
            return tmp.count();
        }
        case TIME_STAMP_S: {
            std::chrono::time_point<std::chrono::system_clock, std::chrono::seconds> timePoint = std::chrono::time_point_cast<std::chrono::seconds>(std::chrono::system_clock::now());
            auto tmp = std::chrono::duration_cast<std::chrono::seconds>(timePoint.time_since_epoch());
            return tmp.count();
        }
        case TIME_STAMP_MIN: {
            std::chrono::time_point<std::chrono::system_clock, std::chrono::minutes> timePoint = std::chrono::time_point_cast<std::chrono::minutes>(std::chrono::system_clock::now());
            auto tmp = std::chrono::duration_cast<std::chrono::minutes>(timePoint.time_since_epoch());
            return tmp.count();
        }
        case TIME_STAMP_H: {
            std::chrono::time_point<std::chrono::system_clock, std::chrono::hours> timePoint = std::chrono::time_point_cast<std::chrono::hours>(std::chrono::system_clock::now());
            auto tmp = std::chrono::duration_cast<std::chrono::hours>(timePoint.time_since_epoch());
            return tmp.count();
        }
        default:{
            std::cout << "time stamp type is invalid" << std::endl;
            return 0;
        }
    }


    return 0;
}

std::string GetMsTimeStamp()
{
    uint64_t timeCount = GetTimeCount(TIME_STAMP_MS);

    time_t milli = timeCount + XR_ZONE_TIME_MS_RATIO_E8; // 此处转化为东八区北京时间，如果是其它时区需要按需求修改
    auto mTime = static_cast<std::chrono::milliseconds>(milli);
    auto tp = std::chrono::time_point<std::chrono::system_clock, std::chrono::milliseconds>(mTime);
    auto tt= std::chrono::system_clock::to_time_t(tp);
    std::tm* now = gmtime(&tt);
    char timeMsg[256] = { 0 }; // 256:buff
    sprintf_s(timeMsg, 255,"%4d-%02d-%02d %02d:%02d:%02d:%04d", now->tm_year + 1900, now->tm_mon + 1, now->tm_mday, now->tm_hour, now->tm_min, now->tm_sec, static_cast<int>(milli % 1000));
    return std::string(timeMsg);
}