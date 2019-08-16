#include <stdio.h>
#include <stdlib.h>
#include <headers/midifile.h>


int main(int argc, char **argv) {
    Midifile *midifile;
    int error_code;

    if (argc < 2) {
        printf("Usage: %s [filename]\n", argv[0]);
        return EXIT_FAILURE;
    }
    midifile = midiface_open_file(argv[1]);
    if ((error_code = midifile_get_last_error()) != MIDIFILE_OK) {
        printf("invalid file (0x%x)", error_code);
        midiface_close_midifile(midifile);
        return EXIT_FAILURE;
    }
    midiface_dump_midifile_header(midifile);
    midiface_close_midifile(midifile);

    return EXIT_SUCCESS;
}
