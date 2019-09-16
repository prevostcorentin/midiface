#ifndef MIDIFACE_ERRUTILS_H
#define MIDIFACE_ERRUTILS_H

#define FATAL 0b1000000000000000000000000000000
#define MIDIFILE_OK 0x01
#define WRONG_MTHD  (0x02 + FATAL)
#define WRONG_MTRK 0x03
#define FILE_OPENING (0x04 + FATAL)
#define NOT_IMPLEMENTED (0x05 + FATAL)
#define READ_EXCEPTION (0x06 + FATAL)
#define NO_SOURCE (0x07 + FATAL)
#define NO_SOURCE_HEADER 0x08

#define MAX_ERRORS 256

#define ERROR_STRING_HEADER "ERROR"
#define FATAL_STRING_HEADER "FATAL ERROR"

unsigned int midiface_pop_last_error();
void midiface_throw_error(unsigned int code);
extern unsigned int midifile_errors[MAX_ERRORS];
extern int err_count;

#endif
