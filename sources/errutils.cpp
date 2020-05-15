#ifdef CMAKE_BUILD
    #include <headers/errutils.hpp>
    #include <headers/logger.hpp>
#else
    #include "../headers/errutils.hpp"
    #include "../headers/logger.hpp"
#endif

#include <cstring>
#include <cerrno>
#include <cstdio>
#include <cstdlib>

bool errutils_global_quit_on_fatal = true;
unsigned int midifile_errors[MAX_ERRORS] = {MIDIFILE_OK};
int err_count=0;

void midiface_turn_on_quit_on_fatal() {
    errutils_global_quit_on_fatal = true;
}

void midiface_turn_off_quit_on_fatal() {
    errutils_global_quit_on_fatal = false;
}

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
    char *error_string = (char*)malloc(512 * sizeof(char));
    if (code == FILE_OPENING) {
        sprintf_s(error_string, 64, "Can not open file");
    } else if (code == WRONG_MTHD) {
        sprintf_s(error_string, 64, "%s", "Wrong file type (probably not a MIDI file format)");
    } else if (code == WRONG_MTRK) {
        sprintf_s(error_string, 64, "%s", "Wrong track type");
    } else if (code == READ_EXCEPTION) {
        sprintf_s(error_string, 64, "Unable to read from file");
    } else if (code == NOT_IMPLEMENTED) {
        sprintf_s(error_string, 64, "Not implemented yet");
    } else if (code == NO_SOURCE) {
        sprintf_s(error_string, 64, "Source is NULL");
    } else if (code == NO_SOURCE_HEADER) {
        sprintf_s(error_string, 64, "Source does not carry a header");
    } else {
        sprintf_s(error_string, 64, "Unknown error");
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
    if (errutils_global_quit_on_fatal && (code & fatal_code)) {
        send_log(LogLevel::MF_ERROR, (char*)"[!] FATAL -> %s", error_string);
        free(error_string);
        exit(EXIT_FAILURE);
    } else {
        send_log(LogLevel::MF_ERROR, (char*)"%s", error_string);
        free(error_string);
    }
}
