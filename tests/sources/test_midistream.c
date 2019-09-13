#include <headers/midistream.h>
#include <headers/miditrack.h>

#include <stdio.h>
#include <malloc.h>


char two_tracks_midifile_data[52] = {'M', 'T', 'h', 'd', // 1: MIDI track header
                                     0x00, 0x00, 0x00, 0x06, // 4: Length = 6
                                     0x00, 0x00, 0x00, 0x01, // 8: Multi-track file
                                     0x00, 0x00, 0x00, 0x02, // 12: 2 tracks
                                     0x00, 0x00, 0x00, 96, // 16: 96 time per quarter note
                                     'M', 'T', 'r', 'k', // 20: First track
                                     0x00, 0x00, 0x00, 0x08, // 24: 8 bytes long
                                     0x00, 0x00, 0x00, 0x00, // 28: Delta-time to 0
                                     0x00, 0x00, 0x00, 0x00, // 32: Playing C0
                                     'M', 'T', 'r', 'k', // 36: Second track
                                     0x00, 0x00, 0x00, 0x08, // 40: 8 bytes long
                                     0x00, 0x00, 0x00, 0x00, // 44: Delta-time to 0
                                     0x00, 0x00, 0x00, 0x00 // 48: Playing C0
};

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
    MIDIStream *midistream = midiface_create_stream(IMMUTABLE);
    midiface_open_stream_source(midistream, "tests/files/SuperMario64.mid");
    MIDIFile *midifile = midiface_get_stream_source(midistream);
    CU_ASSERT_EQUAL(midifile->header->length, 6);
    CU_ASSERT_EQUAL(midifile->header->format, 1);
    CU_ASSERT_EQUAL(midifile->header->ntracks, 3);
    CU_ASSERT_EQUAL(midifile->header->division, 1024);
    midiface_close_stream(midistream);
}

void test_midistream_get_stream_tracks_count() {
    MIDIFile midifile;
    MIDIStream midistream;
    midifile.file = fmemopen(two_tracks_midifile_data, 52, "rb");
    midistream.type = IMMUTABLE;
    midistream.source = &midifile;

    const unsigned int real_tracks_count = midiface_get_stream_tracks_count(&midistream);

    CU_ASSERT_EQUAL(real_tracks_count, 2);
    fclose(midifile.file);
}

void test_midistream_file_get_tracks() {
    MIDIFile midifile;
    MIDIStream midistream;
    midifile.file = fmemopen(two_tracks_midifile_data, 52, "r");
    midistream.type = IMMUTABLE;
    midistream.source = &midifile;
    midifile.header = midiface_get_stream_source(&midistream);

    MIDITrack **tracks = midiface_get_stream_tracks(&midistream);

    CU_ASSERT_EQUAL(tracks[0]->length, 8);
    CU_ASSERT_EQUAL(tracks[1]->length, 8);
    free(tracks[0]);
    free(tracks[1]);
}

void init_midistream_suite() {
    CU_pSuite stream_test_suite = CU_add_suite("Test stream reading/writing", NULL, NULL);
    CU_add_test(stream_test_suite, "Test that an immutable stream from a file on the system is correct",
                test_immutable_stream);
    CU_add_test(stream_test_suite, "Test that an immutable stream from a file gets its source correctly",
                test_midistream_file_get_source);
    CU_add_test(stream_test_suite, "Test that real tracks count from an immutable stream is correct",
                test_midistream_get_stream_tracks_count);
    CU_add_test(stream_test_suite, "Test getting track from an immutable stream file",
                test_midistream_file_get_tracks);
}
