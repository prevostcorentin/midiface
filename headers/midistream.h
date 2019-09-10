#ifndef MIDIFACE_MIDISTREAM_H
#define MIDIFACE_MIDISTREAM_H

#include <headers/midiheader.h>

#include <stdio.h>

enum Stream_Type {
    IMMUTABLE, CONTINUOUS, LISTENING
};

typedef struct {
    enum Stream_Type type;
    void *source;
} MIDIStream;

MIDIStream *midiface_create_stream(enum Stream_Type);

void midiface_open_stream_source(MIDIStream *, const char *);

void midiface_dump_stream_header(MIDIStream *);

MIDIHeader *midiface_get_stream_header(MIDIStream *);

int midiface_get_stream_length(const MIDIStream *);

void midiface_close_stream(MIDIStream *);

#endif //MIDIFACE_MIDISTREAM_H
