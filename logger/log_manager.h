#ifndef _log_manager_h_
#define _log_manager_h_

#include <stdio.h>
#include <stdbool.h>
#include <time.h>
#include <stdarg.h>
#include <stdbool.h>

typedef enum
{
    LOG_LEVEL_DEBUG,
    LOG_LEVEL_INFO,
    LOG_LEVEL_WARN,
    LOG_LEVEL_ERROR
} LogLevel;

void log_manager_init(LogLevel min_level);
void log_message(LogLevel level, const char *file, int line, const char *fmt, ...);

#define log_debug(...) log_message(LOG_LEVEL_DEBUG, __FILE__, __LINE__, __VA_ARGS__)
#define log_info(...)  log_message(LOG_LEVEL_INFO, __FILE__, __LINE__, __VA_ARGS__)
#define log_warn(...)  log_message(LOG_LEVEL_WARN, __FILE__, __LINE__, __VA_ARGS__)
#define log_error(...) log_message(LOG_LEVEL_ERROR, __FILE__, __LINE__, __VA_ARGS__)

#endif