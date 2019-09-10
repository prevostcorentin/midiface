#include "types.h"
#include "errutils.h"
#include "midiheader.h"

#include <stdio.h>

typedef struct {
    MIDIHeader *header;
    FILE *file;
} MIDIFile;

MIDIFile *midiface_open_file(const char *filename);

void midiface_dump_midifile_header(const MIDIFile *midifile);

void midiface_close_midifile(MIDIFile *midifile);
bool midiface_validate_header(byte_t *bytes);
