#ifndef MIDIFACE_TEST_FIXTURES_H
#define MIDIFACE_TEST_FIXTURES_H

/*
char header_only_data[MIDIHEADER_LENGTH] = {'M', 'T', 'h', 'd', // 1: MIDI file header
                                            0x00, 0x00, 0x00, 0x06, // 4: Length = 6
                                            0x00, 0x01, // 6: Multi-track file
                                            0x00, 0x02, // 8: 2 tracks
                                            0x00, 96};  // 10: division 96

char two_tracks_data[46] = {'M', 'T', 'h', 'd', // 1: MIDI file header
                            0x00, 0x00, 0x00, 0x06, // 4: Length = 6
                            0x00, 0x01, // 8: Multi-track file
                            0x00, 0x02, // 12: 2 tracks
                            0x00, 96, // 16: 96 time per quarter note
                            'M', 'T', 'r', 'k', // 20: First track
                            0x00, 0x00, 0x00, 0x08, // 24: 8 bytes long
                            0x00, 0x00, 0x00, 0x00, // 28: Delta-time to 0
                            0x00, 0x00, 0x00, 0x00, // 32: Playing C0
                            'M', 'T', 'r', 'k', // 36: Second track
                            0x00, 0x00, 0x00, 0x08, // 40: 8 bytes long
                            0x00, 0x00, 0x00, 0x00, // 44: Delta-time to 0
                            0x00, 0x00, 0x00, 0x00}; // 48: Playing C0
*/

#endif //MIDIFACE_TEST_FIXTURES_H
