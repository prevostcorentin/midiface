#include "types.h"
#include "errutils.h"

typedef struct {
	int format;
	int header_length;
	int track_chunks_number;
	int division;
} Midifile;

Midifile* midiface_open_file(const char *filename);
void midiface_dump_midifile_header(Midifile *midifile);
void midiface_close_midifile(Midifile *midifile);
bool midiface_validate_header(byte_t *bytes);
