#include <headers/errutils.h>
#include <headers/logger.h>

#include <errno.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

unsigned int midifile_errors[MAX_ERRORS] = {MIDIFILE_OK};
int err_count=0;


unsigned int midiface_pop_last_error() {
    const unsigned int error = midifile_errors[0];
    for (int i = 0; i < err_count; i++) {
      midifile_errors[i] = midifile_errors[i + 1];
    }
    if (err_count >= 0) {
      err_count = err_count - 1;
    }
    return error;
}

char *_get_last_error_string(const unsigned int code) {
    char *error_string = malloc(512 * sizeof(char));
    if (code == FILE_OPENING) {
        sprintf(error_string, "Can not open file - %s", strerror(errno));
    } else if (code == WRONG_MTHD) {
        sprintf(error_string, "Wrong header type (seems not to be a MIDI file format)");
    } else if (code == READ_EXCEPTION) {
        sprintf(error_string, "Unable to read from file - %s", strerror(errno));
    } else if (code == NOT_IMPLEMENTED) {
        sprintf(error_string, "Not implemented yet");
    } else if (code == NO_SOURCE) {
        sprintf(error_string, "Source is NULL");
    } else if (code == NO_SOURCE_HEADER) {
        sprintf(error_string, "Source does not carry a header");
    } else {
        sprintf(error_string, "Unknown error - %s", strerror(errno));
    }
    return error_string;
}

void _add_error(const unsigned int code) {
   midifile_errors[err_count] = code;
   err_count = err_count + 1;
}

void midiface_throw_error(const unsigned int code) {
    _add_error(code);
    char *error_string = _get_last_error_string(code);
    const static unsigned int fatal_code = FATAL;
    if (code & fatal_code) {
        send_log(ERROR, "[!] FATAL -> %s", error_string);
        free(error_string);
        exit(EXIT_FAILURE);
    } else {
        send_log(ERROR, "%s", error_string);
        free(error_string);
    }
}
