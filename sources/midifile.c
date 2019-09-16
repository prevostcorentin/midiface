#include <headers/midifile.h>
#include <headers/memutils.h>
#include <headers/logger.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

MIDIFile *midiface_create_file(FILE *file_descriptor) {
    MIDIFile *midi_file = malloc(sizeof(MIDIFile));
    midi_file->file = file_descriptor;
    midi_file->header = midiface_read_header(file_descriptor);
    return midi_file;
}

MIDIFile *midiface_open_file(const char *filename) {
    FILE *file_descriptor;
    if (NULL == (file_descriptor = fopen(filename, "rb"))) {
        midiface_throw_error(FILE_OPENING);
    }
    MIDIFile *midi_file = midiface_create_file(file_descriptor);
    send_log(DEBUG, "MIDIFile@%p created with file@%p", midi_file, midi_file->file);
    return midi_file;
}

void midiface_close_midifile(MIDIFile *midifile) {
    send_log(DEBUG, "freeing MIDIFile@%p with file@%p", midifile, midifile->file);
    fclose(midifile->file);
    free(midifile->header);
    free(midifile);
}
