
#ifndef TIMESTAMP_H
#define TIMESTAMP_H

#include <chrono>
#include <string>
#include <ctime>
#include <cstdio>

static std::string get_time_stamp_ms()
{
    auto time_point = std::chrono::time_point_cast<std::chrono::milliseconds>(std::chrono::system_clock::now()) + std::chrono::hours(8);
    auto c_time = std::chrono::system_clock::to_time_t(time_point);
    auto count = time_point.time_since_epoch().count();
    std::tm* now = gmtime(&c_time);
    char msg_buffer[64] = { 0 };
    sprintf(msg_buffer, "%4d-%02d-%02d %02d:%02d:%02d.%04d", now->tm_year + 1900, now->tm_mon + 1, now->tm_mday, now->tm_hour, now->tm_min, now->tm_sec, static_cast<int>(count % 1000));
    return std::string(msg_buffer);
}

static std::string get_time_stamp_sec()
{
    auto time_point = std::chrono::time_point_cast<std::chrono::seconds>(std::chrono::system_clock::now()) + std::chrono::hours(8);
    auto c_time = std::chrono::system_clock::to_time_t(time_point);
    std::tm* now = gmtime(&c_time);
    char msg_buffer[64] = { 0 };
    sprintf(msg_buffer, "%4d-%02d-%02d %02d:%02d:%02d", now->tm_year + 1900, now->tm_mon + 1, now->tm_mday, now->tm_hour, now->tm_min, now->tm_sec);
    return std::string(msg_buffer);
}

#endif
