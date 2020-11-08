#include "../../headers/midistream.hpp"
#include "../../headers/miditrack.hpp"

#include <stdio.h>
#include <malloc.h>

#include "fixtures.cpp"
#include "test_api.cpp"

/*
void test_immutable_stream_header_ok() {
    MIDIStream *stream = create_in_memory_midistream(IMMUTABLE, header_only_data, MIDIHEADER_LENGTH);

    MIDIHeader *header = midiface_get_stream_header(stream);
    const int stream_length = midiface_get_stream_length(stream);

    CU_ASSERT_EQUAL(MIDIHEADER_LENGTH, stream_length);
    CU_ASSERT_EQUAL(header->length, 6);
    CU_ASSERT_EQUAL(header->format, 1);
    CU_ASSERT_EQUAL(header->ntracks, 2);
    CU_ASSERT_EQUAL(header->division, 96);
    midiface_close_stream(stream);
}

void test_midistream_file_get_source() {
    MIDIStream *midistream = create_in_memory_midistream(IMMUTABLE, header_only_data, MIDIHEADER_LENGTH);

    MIDIFile *midifile = midiface_get_stream_source(midistream);

    CU_ASSERT_EQUAL(midifile->header->length, 6);
    CU_ASSERT_EQUAL(midifile->header->format, 1);
    CU_ASSERT_EQUAL(midifile->header->ntracks, 2);
    CU_ASSERT_EQUAL(midifile->header->division, 96);
    midiface_close_stream(midistream);
}

void test_midistream_get_stream_tracks_count() {
    MIDIStream *stream = create_in_memory_midistream(IMMUTABLE, two_tracks_data, 46);

    const unsigned int real_tracks_count = midiface_get_stream_tracks_count(stream);

    CU_ASSERT_EQUAL(real_tracks_count, 2);
    midiface_close_stream(stream);
}

void test_midistream_file_get_tracks() {
    MIDIStream *stream = create_in_memory_midistream(IMMUTABLE, two_tracks_data, 46);

    MIDITrack **tracks = midiface_get_stream_tracks(stream);

    CU_ASSERT_EQUAL(tracks[0]->length, 8);
    CU_ASSERT_EQUAL(tracks[1]->length, 8);
    free(tracks[0]);
    free(tracks[1]);
    midiface_close_stream(stream);
}

void init_midistream_suite() {
    CU_pSuite stream_test_suite = CU_add_suite("Test stream reading/writing", NULL, NULL);
    CU_add_test(stream_test_suite, "Test that an immutable stream header is OK",
                test_immutable_stream_header_ok);
    CU_add_test(stream_test_suite, "Test that an immutable stream from a file gets its source correctly",
                test_midistream_file_get_source);
    CU_add_test(stream_test_suite, "Test that real tracks count from an immutable stream is correct",
                test_midistream_get_stream_tracks_count);
    CU_add_test(stream_test_suite, "Test getting track from an immutable stream file",
                test_midistream_file_get_tracks);
}
*/