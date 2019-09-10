#include <headers/errutils.h>
#include <headers/logger.h>

#include <errno.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

unsigned int midifile_errors[MAX_ERRORS] = {MIDIFILE_OK};
int err_count=0;


unsigned int midifile_get_last_error() {
    const unsigned int error = midifile_errors[0];
    for (int i = 0; i < err_count; i++) {
      midifile_errors[i] = midifile_errors[i + 1];
    }
    if (err_count >= 0) {
      err_count = err_count - 1;
    }
    return error;
}

char *midifile_get_last_error_string(const unsigned int code) {
    char *error_string = malloc(512 * sizeof(char));
    if (code == FILE_NOT_FOUND) {
        send_log(ERROR, "%s - %s", "Can not open file", strerror(errno));
    } else if (code == WRONG_MTHD) {
        send_log(ERROR, "Wrong track header type (probably not a MIDI file format)");
    } else {
        send_log(ERROR, "Unknown error - %s", strerror(errno));
    }
    return error_string;
}

void midifile_add_error(const unsigned int code) {
   midifile_errors[err_count] = code;
   err_count = err_count + 1;
}

void midifile_throw_error(const unsigned int code) {
    midifile_add_error(code);
    const char *error_string = midifile_get_last_error_string(code);
    const static unsigned int fatal_code = FATAL;
    if (code & fatal_code) {
        fprintf(stdout, "%s: %s", FATAL_STRING_HEADER, error_string);
        exit(EXIT_FAILURE);
    }
    fprintf(stdout, "%s: %s", ERROR_STRING_HEADER, error_string);
}
