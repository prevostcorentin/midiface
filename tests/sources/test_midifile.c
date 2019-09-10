#include <headers/midifile.h>

void midi_file_valid_header_test() {
    const MIDIFile *valid_MIDIFile = midiface_open_file("tests/files/SuperMario64.mid");
    CU_ASSERT_EQUAL(valid_MIDIFile->header->length, 6);
    CU_ASSERT_EQUAL(valid_MIDIFile->header->format, 1);
    CU_ASSERT_EQUAL(valid_MIDIFile->header->ntracks, 3);
    CU_ASSERT_EQUAL(valid_MIDIFile->header->division, 1024);
}

void init_midifile_suite() {
    CU_pSuite file_test_suite = CU_add_suite("Test file reading", NULL, NULL);
    CU_add_test(file_test_suite, "Test that a valid file header is read correctly",
                midi_file_valid_header_test);
}
