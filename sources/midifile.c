#include <headers/midifile.h>
#include <headers/memutils.h>
#include <headers/logger.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

MIDIFile *midiface_open_file(const char *filename) {
    FILE *file_descriptor;
    char mthd[4];
    MIDIFile *midifile = malloc(sizeof(MIDIFile));
    midifile->header = malloc(sizeof(MIDIHeader));
    if (NULL == (file_descriptor = fopen(filename, "rb"))) {
        midiface_throw_error(FILE_OPENING);
    }
    read_chunk(file_descriptor, mthd);
    if (!(midiface_validate_header(mthd))) {
        midiface_throw_error(WRONG_MTHD);
    }
    midifile->file = file_descriptor;
    midifile->header->length = read_unsigned_integer(file_descriptor, 4);
    midifile->header->format = read_unsigned_integer(file_descriptor, 2);
    midifile->header->ntracks = read_unsigned_integer(file_descriptor, 2);
    midifile->header->division = read_unsigned_integer(file_descriptor, 2);
    send_log(DEBUG, "MIDIFile@%p created with file@%p", midifile, midifile->file);
    return midifile;
}

bool midiface_validate_header(char *bytes) {
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
