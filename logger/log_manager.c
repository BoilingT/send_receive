#include "log_manager.h"

static LogLevel current_log_level = LOG_LEVEL_INFO; // Default log level

void log_manager_init(LogLevel min_level)
{
    current_log_level = min_level;
}

void log_message(LogLevel level, const char *file, int line, const char *fmt, ...)
{
    if (level < current_log_level)
    {
        return;
    }

    // Get the target stream (stdout for INFO, stderr for others)
    FILE *stream = (level == LOG_LEVEL_INFO) ? stdout : stderr;

    // Get current time for timestamp
    time_t     timer;
    char       time_buffer[26];
    struct tm *tm_info;
    time(&timer);
    tm_info = localtime(&timer);
    strftime(time_buffer, 26, "%H:%M:%S", tm_info);

    // Print log prefix (timestamp and level)
    fprintf(stream, "[%s] ", time_buffer);
    switch (level)
    {
    case LOG_LEVEL_DEBUG : fprintf(stream, "DEBUG: "); break;
    case LOG_LEVEL_INFO  : fprintf(stream, "INFO:  "); break;
    case LOG_LEVEL_WARN  : fprintf(stream, "WARN:  "); break;
    case LOG_LEVEL_ERROR : fprintf(stream, "ERROR: "); break;
    }

    // Print the actual message
    va_list args;
    va_start(args, fmt);
    vfprintf(stream, fmt, args);
    if (current_log_level == LOG_LEVEL_DEBUG || level > LOG_LEVEL_INFO)
    {
        fprintf(stream, " (%s:%d)\n", file, line);
    }
    else
    {
        fprintf(stream, "\n");
    }
    va_end(args);
}