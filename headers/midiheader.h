#ifndef MIDIFACE_MIDIHEADER_H
#define MIDIFACE_MIDIHEADER_H

#define MIDIHEADER_LENGTH 20

typedef struct {
    unsigned int format;
    unsigned int length;
    unsigned int ntracks;
    unsigned int division;
} MIDIHeader;

#endif //MIDIFACE_MIDIHEADER_H
