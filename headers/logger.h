#ifndef MIDIFACE_LOGGER_H
#define MIDIFACE_LOGGER_H

#include <stdio.h>

enum LogLevel {
    DEBUG = 0b00000001, INFO = 0b00000011, ERROR = 0b00000111
};

void add_log_output(FILE *output_stream, enum LogLevel);

void send_log(enum LogLevel, char *message_format, ...);

void clear_logs_stream();

#endif //MIDIFACE_LOGGER_H
