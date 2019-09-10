#include <headers/midifile.h>
#include <headers/memutils.h>
#include <headers/logger.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

MIDIFile *midiface_open_file(const char *filename) {
    FILE *fptr;
    byte_t mthd[4];
    MIDIFile *midifile = malloc(sizeof(MIDIFile));
    midifile->header = malloc(sizeof(MIDIHeader));
    if ((fptr = fopen(filename, "r")) == NULL) {
        midifile_throw_error(FILE_NOT_FOUND);
    }
    fread(mthd, 4, 1, fptr);
    if (!(midiface_validate_header(mthd))) {
        midifile_throw_error(WRONG_MTHD);
    }
    midifile->file = fptr;
    midifile->header->length = read_unsigned_integer(fptr, 4);
    midifile->header->format = read_unsigned_integer(fptr, 2);
    midifile->header->ntracks = read_unsigned_integer(fptr, 2);
    midifile->header->division = read_unsigned_integer(fptr, 2);
    send_log(DEBUG, "MIDIFile@%p created with file@%p", midifile, midifile->file);
    return midifile;
}

bool midiface_validate_header(byte_t *bytes) {
    static const unsigned char mthd[] = {0x4d, 0x54, 0x68, 0x64};
    return memcmp(bytes, mthd, sizeof mthd) == 0;
}

void midiface_close_midifile(MIDIFile *midifile) {
    /*
    if(midifile->tracks != NULL) {
       free(midifile->tracks);
    }
    */
    send_log(DEBUG, "freeing MIDIFile@%p with file@%p", midifile, midifile->file);
    fclose(midifile->file);
    free(midifile);
}
