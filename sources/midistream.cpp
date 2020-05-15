#ifdef CMAKE_BUILD
    #include <headers/memutils.hpp>
    #include <headers/midifile.hpp>
    #include <headers/midistream.hpp>
    #include <headers/midispec.hpp>
    #include <headers/errutils.hpp>
    #include <headers/logger.hpp>
#else
    #include "../headers/memutils.hpp"
    #include "../headers/midifile.hpp"
    #include "../headers/midistream.hpp"
    #include "../headers/midispec.hpp"
    #include "../headers/errutils.hpp"
    #include "../headers/logger.hpp"
#endif

#include <malloc.h>
#include <stdio.h>
#include <string.h>

MIDIStream *midiface_create_stream(const enum class StreamType type) {
    MIDIStream *stream = (MIDIStream*)malloc(sizeof(MIDIStream));
    stream->type = type;
    send_log(LogLevel::MF_DEBUG, (char*)"Stream created @%p", stream);
    return stream;
}

void midiface_open_stream_source(MIDIStream *stream, const char *source_name) {
    if (stream->type == StreamType::IMMUTABLE) {
        stream->source = midiface_open_file(source_name);
    } else if (stream->type == StreamType::CONTINUOUS) {
        send_log(LogLevel::MF_ERROR, (char*)"Continuous stream source opening not implemented");
        midiface_throw_error(NOT_IMPLEMENTED);
    } else if (stream->type == StreamType::LISTENING) {
        send_log(LogLevel::MF_ERROR, (char*)"Listening stream source opening not implemented");
        midiface_throw_error(NOT_IMPLEMENTED);
    }
}

int midiface_get_stream_length(MIDIStream *stream) {
    size_t source_size = -1;
    if (stream->type == StreamType::IMMUTABLE) {
        MIDIFile *midifile = (MIDIFile *) midiface_get_stream_source(stream);
        const size_t initial_position = seek_remind(midifile->file, 0, SEEK_END);
        source_size = seek_remind(midifile->file, initial_position, SEEK_SET);
    } else if (stream->type == StreamType::CONTINUOUS || 
               stream->type == StreamType::LISTENING) {
        // CONTINUOUS and LISTENING have infinite length because it sends at any time any data
        // A size should be calculated after it has been closed.
        source_size = -1;
    }
    return source_size;
}

void midiface_close_stream(MIDIStream *stream) {
    midiface_close_midifile((MIDIFile*)stream->source);
    send_log(LogLevel::MF_DEBUG, (char*)"Freeing stream @%p", stream);
    free(stream);
}

void midiface_dump_stream_header(MIDIStream *stream) {
    const MIDIHeader *header = midiface_get_stream_header(stream);
    printf("format: ([Naming not implemented]) (%d)\n"
           "number of tracks: %d\n"
           "division: %d\n",
           header->format,
           header->ntracks,
           header->division);
}

MIDIHeader *midiface_get_stream_header(MIDIStream *stream) {
    MIDIHeader *header = NULL;
    if (stream->type == StreamType::IMMUTABLE) {
        MIDIFile *source = (MIDIFile *) midiface_get_stream_source(stream);
        if (source->header == NULL) {
            midiface_throw_error(NO_SOURCE_HEADER);
        }
        header = source->header;
    } else if (stream->type == StreamType::CONTINUOUS) {
        send_log(LogLevel::MF_ERROR, (char*)"Continuous stream header getting not implemented");
        midiface_throw_error(NOT_IMPLEMENTED);
    } else if (stream->type == StreamType::LISTENING) {
        send_log(LogLevel::MF_ERROR, (char*)"Listening stream header getting not implemented");
        midiface_throw_error(NOT_IMPLEMENTED);
    }
    return header;
}

void *midiface_get_stream_source(MIDIStream *stream) {
    if (stream->type == StreamType::IMMUTABLE) {
        MIDIFile* source = (MIDIFile*)stream->source;
        if (source == NULL) {
            midiface_throw_error(NO_SOURCE);
        }
        return source;
    }
    else if (stream->type == StreamType::CONTINUOUS) {
        send_log(LogLevel::MF_ERROR, (char*)"Continuous stream header getting not implemented");
        midiface_throw_error(NOT_IMPLEMENTED);
    }
    else if (stream->type == StreamType::LISTENING) {
        send_log(LogLevel::MF_ERROR, (char*)"Listening stream header getting not implemented");
        midiface_throw_error(NOT_IMPLEMENTED);
    }
}

int midiface_validate_track_header(unsigned char bytes[4]) {
    static const unsigned char mtrk[] = {'M', 'T', 'r', 'k'};
    return memcmp(bytes, mtrk, sizeof mtrk) == 0;
}

MIDITrack *_get_next_track(FILE *file_descriptor) {
    MIDITrack *track = NULL;
    char mtrk[4];
    read_chunk(file_descriptor, mtrk);
    if (feof(file_descriptor)) {
        return NULL;
    }
    if (!midiface_validate_track_header((unsigned char*)mtrk)) {
        midiface_throw_error(WRONG_MTRK);
    } else {
        track = (MIDITrack*)malloc(sizeof(MIDITrack));
        track->length = read_unsigned_integer(file_descriptor, 4);
        track->events = NULL;
        secure_fseek(file_descriptor, track->length, SEEK_CUR);
    }
    return track;
}

MIDITrack **midiface_get_stream_tracks(MIDIStream *midi_stream) {
    if (midi_stream->type == StreamType::IMMUTABLE) {
        MIDIFile* source = (MIDIFile*)midiface_get_stream_source(midi_stream);
        const unsigned int tracks_count = midiface_get_stream_tracks_count(midi_stream);
        rewind(source->file);
        secure_fseek(source->file, MIDIHEADER_LENGTH, SEEK_CUR);
        MIDITrack** read_tracks = (MIDITrack**)malloc(sizeof(void*) * tracks_count);
        for (unsigned int i = 0; i < tracks_count; i++) {
            read_tracks[i] = _get_next_track(source->file);
        }
        return read_tracks;
    }
    else if (midi_stream->type == StreamType::CONTINUOUS) {
        send_log(LogLevel::MF_ERROR, (char*)"Continuous stream header getting not implemented");
        midiface_throw_error(NOT_IMPLEMENTED);
    }
    else if (midi_stream->type == StreamType::LISTENING) {
        send_log(LogLevel::MF_ERROR, (char*)"Listening stream header getting not implemented");
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