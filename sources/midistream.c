#include <headers/midifile.h>
#include <headers/midistream.h>
#include <headers/midispec.h>
#include <headers/errutils.h>
#include <headers/logger.h>

#include <malloc.h>
#include <stdio.h>

#define \
    STREAM_TYPE_AS_STRING(STREAM_TYPE) \
    ({ \
        (STREAM_TYPE) == IMMUTABLE ? "IMMUTABLE" : \
        (STREAM_TYPE) == CONTINUOUS ? "CONTINUOUS" : \
        (STREAM_TYPE) == LISTENING ? "LISTENING" : \
        "WRONG FORMAT"; \
    })

MIDIStream *midiface_create_stream(const enum Stream_Type type) {
    MIDIStream *stream = malloc(sizeof(MIDIStream));
    stream->type = type;
    send_log(DEBUG, "%s@%p stream created", STREAM_TYPE_AS_STRING(type), stream);
    return stream;
}

// Renaming because "source" is confusing
void midiface_open_stream_source(MIDIStream *stream, const char *source_name) {
    if (stream->type == IMMUTABLE) {
        stream->source = midiface_open_file(source_name);
    } else if (stream->type == CONTINUOUS) {
        send_log(ERROR, "Continuous stream source opening not implemented");
        midifile_throw_error(NOT_IMPLEMENTED);
    } else if (stream->type == LISTENING) {
        send_log(ERROR, "Listening stream source opening not implemented");
        midifile_throw_error(NOT_IMPLEMENTED);
    }
}

int midiface_get_stream_length(const MIDIStream *stream) {
    size_t source_size = -1;
    if (stream->type == IMMUTABLE) {
        MIDIFile *midifile = (MIDIFile *) stream->source;
        const size_t initial_position = ftell(midifile->file);
        fseek(midifile->file, 0, SEEK_END);
        source_size = ftell(midifile->file);
        fseek(midifile->file, initial_position, SEEK_SET);
    } else if (stream->type == CONTINUOUS || stream->type == LISTENING) {
        // CONTINUOUS and LISTENING have infinite length because it sends at any time any data
        // A size should be calculated after it has been closed.
        source_size = -1;
    }
    return source_size;
}

void midiface_close_stream(MIDIStream *stream) {
    midiface_close_midifile(stream->source);
    send_log(DEBUG, "freeing %s@%p stream", STREAM_TYPE_AS_STRING(stream->type), stream);
    free(stream);
}

void midiface_dump_stream_header(MIDIStream *stream) {
    const MIDIHeader *header = midiface_get_stream_header(stream);
    printf("format: %s (%d)\n"
           "number of tracks: %d\n"
           "division: %d\n",
           FILE_FORMAT_STRING_DESCRIPTION(header->format),
           header->format,
           header->ntracks,
           header->division);
}

MIDIHeader *midiface_get_stream_header(MIDIStream *stream) {
    MIDIHeader *header = NULL;
    if (stream->type == IMMUTABLE) {
        MIDIFile *source = (MIDIFile *) stream->source;
        header = source->header;
    } else if (stream->type == CONTINUOUS) {
        send_log(ERROR, "Continuous stream header getting not implemented");
        midifile_throw_error(NOT_IMPLEMENTED);
    } else if (stream->type == LISTENING) {
        send_log(ERROR, "Listening stream header getting not implemented");
        midifile_throw_error(NOT_IMPLEMENTED);
    }
    return header;
}