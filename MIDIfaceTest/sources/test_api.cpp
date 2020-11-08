#ifndef MIDIFACE_TEST_API_GUARD
#define MIDIFACE_TEST_API_GUARD

#include "../../headers/midifile.hpp"
#include "../../headers/midistream.hpp"

#include <malloc.h>
/*
MIDIStream *create_in_memory_midistream(const enum Stream_Type type, char *raw_data, const size_t buffer_size) {
    if (type == IMMUTABLE) {
        MIDIStream *stream = midiface_create_stream(IMMUTABLE);
        FILE *file = fmemopen(raw_data, buffer_size, "rb");
        MIDIFile *midi_file = midiface_create_file(file);
        stream->source = midi_file;
        midi_file->header = midiface_read_header(midi_file->file);
        return stream;
    } else if (type == CONTINUOUS) {
        midiface_throw_error(NOT_IMPLEMENTED);
    } else if (type == LISTENING) {
        midiface_throw_error(NOT_IMPLEMENTED);
    } else {
        fprintf(stderr, "No stream type declared");
        midiface_throw_error(FATAL);
    }
}
*/
#endif

