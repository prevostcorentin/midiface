#include "types.h"
#include "errutils.h"

typedef struct {
    unsigned int format;
    unsigned int header_length;
    unsigned int track_chunks_number;
    unsigned int division;
} Midifile;

Midifile* midiface_open_file(const char *filename);

void midiface_dump_midifile_header(const Midifile *midifile);
void midiface_close_midifile(Midifile *midifile);
bool midiface_validate_header(byte_t *bytes);
