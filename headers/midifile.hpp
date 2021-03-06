#ifndef MIDIFACE_MIDIFILE_H
#define MIDIFACE_MIDIFILE_H

#include "midiheader.hpp"
#include "types.hpp"
#include "errutils.hpp"

#include <stdio.h>


typedef struct {
    MIDIHeader *header;
    FILE *file;
} MIDIFile;

MIDIFile *midiface_create_file(FILE *);

MIDIFile *midiface_open_file(const char *filename);
void midiface_close_midifile(MIDIFile *midifile);
bool midiface_validate_header(char *bytes);

#endif
