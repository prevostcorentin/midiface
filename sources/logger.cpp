#ifdef CMAKE_BUILD
    #include <headers/logger.hpp>
#else
    #include "../headers/logger.hpp"
#endif

#include <stdlib.h>
#include <stdarg.h>
#include <string.h>

#include <cstdio>

#define MAX_LOG_STREAMS_COUNT 8

typedef struct LogStream {
    enum class LogLevel log_level;
    FILE *output;
} LogStream;

LogStream *log_streams[MAX_LOG_STREAMS_COUNT] = {NULL};
unsigned int log_streams_count = 0;

void add_log_output(FILE *output, enum LogLevel log_level) {
    LogStream *log_stream = (LogStream*)malloc(sizeof(LogStream));
    log_stream->log_level = log_level;
    log_stream->output = output;
    log_streams[log_streams_count] = log_stream;
    log_streams_count = log_streams_count + 1;
}

char *add_prefix_newline(const enum LogLevel log_level, char *message_format) {
    char *prefixed_log_message_format = (char*)malloc(strlen(message_format) + sizeof(char) * 8);
    if (log_level == LogLevel::MF_DEBUG) {
        sprintf_s(prefixed_log_message_format, 64, "%s: %s\n", "DEBUG", message_format);
    } else if (log_level == LogLevel::MF_ERROR) {
        sprintf_s(prefixed_log_message_format, 64, "%s: %s\n", "ERROR", message_format);
    } else if (log_level == LogLevel::MF_INFO) {
        sprintf_s(prefixed_log_message_format, 64, "%s: %s\n", "INFO", message_format);
    } else {
        sprintf_s(prefixed_log_message_format, 64, "%s\n", message_format);
    }
    return prefixed_log_message_format;
}

void send_log(enum class LogLevel log_level, char *message_format, ...) {
    va_list args_copy, args_save;
    va_start(args_save, message_format);
    LogStream *stream = NULL;
    char *prefixed_message_format = NULL;
    for (unsigned int i = 0; i < log_streams_count; i++) {
        // When vfprintf is called it goes to the end of the variadic arguments
        // so it is necessary to iterate on a copy unless a segmentation error happens
        va_copy(args_copy, args_save);
        stream = log_streams[i];
        if (((int)stream->log_level & (int)log_level) == (int)stream->log_level) {
            prefixed_message_format = add_prefix_newline(log_level, message_format);
            vfprintf(stream->output, prefixed_message_format, args_copy);
            free(prefixed_message_format);
        }
        va_end(args_copy);
    }
    va_end(args_save);
}

void clear_logs_stream() {
    LogStream *stream = NULL;
    for (unsigned int i = 0; i < log_streams_count; i++) {
        stream = log_streams[i];
        fclose(stream->output);
        free(stream);
    }
    log_streams_count = 0;
}