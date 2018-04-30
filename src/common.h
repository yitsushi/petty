#ifndef __COMMON_H
#define __COMMON_H

#include <string.h>
#include <time.h>

#define NO_LOG      0x00
#define ERROR_LEVEL 0x01
#define INFO_LEVEL  0x02
#define DEBUG_LEVEL 0x03

#define ERROR_TAG   "ERROR"
#define INFO_TAG    "INFO"
#define DEBUG_TAG   "DEBUG"

#define LOG_FMT "%s | %-7s | %-15s | %s:%d | "
#define NEWLINE "\n"

#ifndef LOG_LEVEL
#define LOG_LEVEL ERROR_LEVEL
#endif

#define _FILE strrchr(__FILE__, '/') ? strrchr(__FILE__, '/') + 1 : __FILE__

#define PRINTFUNCTION(format, ...) fprintf(stderr, format, __VA_ARGS__)
#define LOG_ARGS(LOG_TAG) timenow(), LOG_TAG, _FILE, __FUNCTION__, __LINE__

#if LOG_LEVEL >= DEBUG_LEVEL
#define LOG_DEBUG(message, args...) PRINTFUNCTION(LOG_FMT message NEWLINE, LOG_ARGS(DEBUG_TAG), ##args)
#else
#define LOG_DEBUG(message, args...)
#endif

#if LOG_LEVEL >= INFO_LEVEL
#define LOG_INFO(message, args...) PRINTFUNCTION(LOG_FMT message NEWLINE, LOG_ARGS(INFO_TAG), ##args)
#else
#define LOG_INFO(message, args...)
#endif

#if LOG_LEVEL >= ERRROR_LEVEL
#define LOG_ERROR(message, args...) PRINTFUNCTION(LOG_FMT message NEWLINE, LOG_ARGS(ERROR_TAG), ##args)
#else
#define LOG_ERROR(message, args...)
#endif

static inline char *timenow()
{
    static char buffer[64];
    time_t rawtime;
    struct tm *timeinfo;

    time(&rawtime);
    timeinfo = localtime(&rawtime);

    strftime(buffer, 64, "%Y-%m-%d %H:%M:%S", timeinfo);

    return buffer;
}

char* concat(const char *s1, const char *s2);

#endif