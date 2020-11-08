#ifndef MIDIFACE_MIDIHEADER_H
#define MIDIFACE_MIDIHEADER_H

#define MIDIHEADER_LENGTH 14

#include <cstdio>

namespace MIDI
{
    typedef struct {
        unsigned int format;
        unsigned int length;
        unsigned int ntracks;
        unsigned int division;
    } Header;

    Header* midiface_read_header(FILE*);
}

#endif //MIDIFACE_MIDIHEADER_H
