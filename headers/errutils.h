#ifndef ERR_UTILS

#define FATAL 0b10000000
#define MIDIFILE_OK 0x01
#define WRONG_MTHD  0x02
#define FILE_NOT_FOUND 0x03

#define MAX_ERRORS 256

int midifile_get_last_error();
void midifile_add_error(int code);

extern int midifile_errors[MAX_ERRORS];
extern int err_count;

#endif
