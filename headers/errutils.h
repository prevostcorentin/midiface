#ifndef ERR_UTILS
#define ERR_UTILS

#define FATAL 0b1000000000000000000000000000000
#define MIDIFILE_OK 0x01
#define WRONG_MTHD  (0x02 + FATAL)
#define FILE_NOT_FOUND (0x03 + FATAL)

#define MAX_ERRORS 256

#define ERROR_STRING_HEADER "ERROR:"
#define FATAL_STRING_HEADER "FATAL ERROR:"

unsigned int midifile_get_last_error();

void midifile_throw_error(unsigned int code);

extern unsigned int midifile_errors[MAX_ERRORS];
extern int err_count;

#endif
