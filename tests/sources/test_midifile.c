#include <headers/midifile.h>
#include <headers/errutils.h>

#include "fixtures.c"

void test_midi_file_valid_header() {
    FILE *file_descriptor = fmemopen(header_only_data, MIDIHEADER_LENGTH, "rb");

    const MIDIFile *valid_MIDIFile = midiface_create_file(file_descriptor);

    CU_ASSERT_EQUAL(valid_MIDIFile->header->length, 6);
    CU_ASSERT_EQUAL(valid_MIDIFile->header->format, 1);
    CU_ASSERT_EQUAL(valid_MIDIFile->header->ntracks, 2);
    CU_ASSERT_EQUAL(valid_MIDIFile->header->division, 96);
}

void test_midifile_open() {
    MIDIFile *midi_file = NULL;

    midi_file = midiface_open_file("tests/files/SuperMario64.mid");

    CU_ASSERT_PTR_NOT_NULL(midi_file->file);
}

void test_open_unexisting() {
    MIDIFile *midi_file = NULL;

    midi_file = midiface_open_file("tests/files/unexisting.mid");

    const unsigned int error_code = midiface_pop_last_error();
    CU_ASSERT_EQUAL(error_code, FILE_OPENING);
    CU_ASSERT_PTR_NULL(midi_file->file);
}

void init_midifile_suite() {
    CU_pSuite file_test_suite = CU_add_suite("Test file reading", NULL, NULL);
    CU_add_test(file_test_suite, "Test that a valid file header is read correctly",
                test_midi_file_valid_header);
    CU_add_test(file_test_suite, "Test that a valid file can be opened",
                test_midifile_open);
    CU_add_test(file_test_suite, "Test that opening a non existing file throws error",
                test_midifile_open);
}
