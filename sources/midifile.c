#include <headers/midifile.h>
#include <headers/memutils.h>
#include <headers/midispec.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

Midifile *midiface_open_file(const char *filename) {
    FILE *fptr;
    byte_t mthd[4];
    Midifile *midifile = malloc(sizeof(Midifile));
    if ((fptr = fopen(filename, "r")) == NULL) {
        midifile_throw_error(FILE_NOT_FOUND);
    }
    fread(mthd, 4, 1, fptr);
    if (!(midiface_validate_header(mthd))) {
        midifile_throw_error(WRONG_MTHD);
    }
    midifile->header_length = read_unsigned_integer(fptr, 4);
    midifile->format = read_unsigned_integer(fptr, 2);
    midifile->track_chunks_number = read_unsigned_integer(fptr, 2);
    midifile->division = read_unsigned_integer(fptr, 2);
    return midifile;
}

bool midiface_validate_header(byte_t *bytes) {
    static const unsigned char mthd[] = {0x4d, 0x54, 0x68, 0x64};
    return memcmp(bytes, mthd, sizeof mthd) == 0;
}

void midiface_dump_midifile_header(const Midifile *midifile) {
    printf("format: %s (%d)\n"
           "number of tracks: %d\n"
           "division: %d\n",
           FILE_FORMAT_STRING_DESCRIPTION(midifile->format),
           midifile->format,
           midifile->track_chunks_number,
           midifile->division);
}

void midiface_close_midifile(Midifile *midifile) {
    /*
    if(midifile->tracks != NULL) {
       free(midifile->tracks);
    }
    */
    free(midifile);
}
