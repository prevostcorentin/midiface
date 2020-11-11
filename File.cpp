#include <memutils.h>
#include <Logger.h>

#include <cstdio>
#include <cstdlib>
#include <cstring>

/*
MIDIFile *midiface_create_file(FILE *file_descriptor) {
    MIDIFile *midi_file = (MIDIFile*)malloc(sizeof(MIDIFile));
    midi_file->file = file_descriptor;
    midi_file->header = midiface_read_header(file_descriptor);
    return midi_file;
}

MIDIFile *midiface_open_file(const char *filename) {
    FILE *file_descriptor;
    MIDIFile *midi_file = NULL;
    fopen_s(&file_descriptor, filename, "wb");
    if (NULL == file_descriptor) {
        midiface_throw_error(FILE_OPENING);
    } else {
        midi_file = midiface_create_file(file_descriptor);
        send_log(LogLevel::MF_DEBUG, (char*)"MIDIFile@%p created with file@%p", midi_file, midi_file->file);
    }
    return midi_file;
}

void midiface_close_midifile(MIDIFile *midifile) {
    send_log(LogLevel::MF_DEBUG, (char*)"freeing MIDIFile@%p with file@%p", midifile, midifile->file);
    fclose(midifile->file);
    free(midifile->header);
    free(midifile);
}
*/
