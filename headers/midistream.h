#ifndef MIDIFACE_MIDISTREAM_H
#define MIDIFACE_MIDISTREAM_H

#include <headers/midiheader.h>
#include <headers/miditrack.h>

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
void *midiface_get_stream_source(MIDIStream *);
void midiface_dump_stream_header(MIDIStream *);
MIDIHeader *midiface_get_stream_header(MIDIStream *);
int midiface_get_stream_length(MIDIStream *);
void midiface_close_stream(MIDIStream *);

unsigned int midiface_get_stream_tracks_count(MIDIStream *midistream);

MIDITrack **midiface_get_stream_tracks(MIDIStream *midistream);

#endif //MIDIFACE_MIDISTREAM_H
