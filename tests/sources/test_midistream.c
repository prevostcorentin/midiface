#include "headers/midistream.h"


/**
 * The immutable stream does not send data continuously, it is often a file read once and closed.
 * This stream has a length because it is ending.
 */
void test_immutable_stream() {
    MIDIStream *stream = midiface_create_stream(IMMUTABLE);
    midiface_open_stream_source(stream, "tests/files/SuperMario64.mid");
    MIDIHeader *header = midiface_get_stream_header(stream);
    const int stream_length = midiface_get_stream_length(stream);
    CU_ASSERT_EQUAL(48700, stream_length);
    CU_ASSERT_EQUAL(header->length, 6);
    CU_ASSERT_EQUAL(header->format, 1);
    CU_ASSERT_EQUAL(header->ntracks, 3);
    CU_ASSERT_EQUAL(header->division, 1024);
    midiface_close_stream(stream);
}

void test_midistream_file_get_source() {
    MIDIStream *stream = midiface_create_stream(IMMUTABLE);
    midiface_open_stream_source(stream, "tests/files/SuperMario64.mid");
    MIDIFile *midifile = midiface_get_stream_source(stream);
    CU_ASSERT_EQUAL(midifile->header->length, 6);
    CU_ASSERT_EQUAL(midifile->header->format, 1);
    CU_ASSERT_EQUAL(midifile->header->ntracks, 3);
    CU_ASSERT_EQUAL(midifile->header->division, 1024);
}

void init_midistream_suite() {
    CU_pSuite stream_test_suite = CU_add_suite("Test stream reading/writing", NULL, NULL);
    CU_add_test(stream_test_suite, "Test that an immutable stream from a file on the system is correct",
                test_immutable_stream);
    CU_add_test(stream_test_suite, "Test that an immutable stream from a file gets its source correctly",
                test_midistream_file_get_source);
}
