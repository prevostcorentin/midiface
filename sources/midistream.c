#include <headers/memutils.h>
#include <headers/midifile.h>
#include <headers/midistream.h>
#include <headers/midispec.h>
#include <headers/errutils.h>
#include <headers/logger.h>

#include <malloc.h>
#include <stdio.h>
#include <string.h>

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

void midiface_open_stream_source(MIDIStream *stream, const char *source_name) {
    if (stream->type == IMMUTABLE) {
        stream->source = midiface_open_file(source_name);
    } else if (stream->type == CONTINUOUS) {
        send_log(ERROR, "Continuous stream source opening not implemented");
        midiface_throw_error(NOT_IMPLEMENTED);
    } else if (stream->type == LISTENING) {
        send_log(ERROR, "Listening stream source opening not implemented");
        midiface_throw_error(NOT_IMPLEMENTED);
    }
}

int midiface_get_stream_length(MIDIStream *stream) {
    size_t source_size = -1;
    if (stream->type == IMMUTABLE) {
        MIDIFile *midifile = (MIDIFile *) midiface_get_stream_source(stream);
        const size_t initial_position = ftell(midifile->file);
        secure_fseek(midifile->file, 0, SEEK_END);
        source_size = ftell(midifile->file);
        secure_fseek(midifile->file, initial_position, SEEK_SET);
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
        MIDIFile *source = (MIDIFile *) midiface_get_stream_source(stream);
        if (source->header == NULL) {
            midiface_throw_error(NO_SOURCE_HEADER);
        }
        header = source->header;
    } else if (stream->type == CONTINUOUS) {
        send_log(ERROR, "Continuous stream header getting not implemented");
        midiface_throw_error(NOT_IMPLEMENTED);
    } else if (stream->type == LISTENING) {
        send_log(ERROR, "Listening stream header getting not implemented");
        midiface_throw_error(NOT_IMPLEMENTED);
    }
    return header;
}

void *midiface_get_stream_source(MIDIStream *stream) {
    if (stream->type == IMMUTABLE) {
        MIDIFile *source = (MIDIFile *) stream->source;
        if (source == NULL) {
            midiface_throw_error(NO_SOURCE);
        }
        return source;
    } else if (stream->type == CONTINUOUS) {
        send_log(ERROR, "Continuous stream header getting not implemented");
        midiface_throw_error(NOT_IMPLEMENTED);
    } else if (stream->type == LISTENING) {
        send_log(ERROR, "Listening stream header getting not implemented");
        midiface_throw_error(NOT_IMPLEMENTED);
    }
}

int midiface_validate_track_header(unsigned char bytes[4]) {
    static const unsigned char mtrk[] = {'M', 'T', 'r', 'k'};
    return memcmp(bytes, mtrk, sizeof mtrk) == 0;
}

MIDITrack *_get_next_track(FILE *file_descriptor) {
    MIDITrack *track = NULL;
    unsigned char mtrk[4];
    read_chunk(file_descriptor, mtrk);
    if (feof(file_descriptor)) {
        return NULL;
    }
    if (!midiface_validate_track_header(mtrk)) {
        midiface_throw_error(WRONG_MTRK);
    } else {
        track = malloc(sizeof(MIDITrack));
        track->length = read_unsigned_integer(file_descriptor, 4);
        track->events = NULL;
        secure_fseek(file_descriptor, track->length, SEEK_CUR);
    }
    return track;
}

MIDITrack **midiface_get_stream_tracks(MIDIStream *midi_stream) {
    if (midi_stream->type == IMMUTABLE) {
        MIDIFile *source = (MIDIFile *) midiface_get_stream_source(midi_stream);
        const unsigned int tracks_count = midiface_get_stream_tracks_count(midi_stream);
        rewind(source->file);
        secure_fseek(source->file, MIDIHEADER_LENGTH, SEEK_CUR);
        MIDITrack **read_tracks = malloc(sizeof(void *) * tracks_count);
        for (unsigned int i = 0; i < tracks_count; i++) {
            read_tracks[i] = _get_next_track(source->file);
        }
        return read_tracks;
    } else if (midi_stream->type == CONTINUOUS) {
        send_log(ERROR, "Continuous stream header getting not implemented");
        midiface_throw_error(NOT_IMPLEMENTED);
    } else if (midi_stream->type == LISTENING) {
        send_log(ERROR, "Listening stream header getting not implemented");
        midiface_throw_error(NOT_IMPLEMENTED);
    }
}

unsigned int midiface_get_stream_tracks_count(MIDIStream *midi_stream) {
    MIDIFile *source = (MIDIFile *) midiface_get_stream_source(midi_stream);
    rewind(source->file);
    secure_fseek(source->file, MIDIHEADER_LENGTH, SEEK_CUR);
    unsigned int tracks_count = 0;
    while (NULL != _get_next_track(source->file)) {
        tracks_count = tracks_count + 1;
    }
    return tracks_count;
}