#ifndef MIDIFACE_MIDITRACK_H
#define MIDIFACE_MIDITRACK_H

typedef struct {
    unsigned int length;
    void *events;
} MIDITrack;

#endif //MIDIFACE_MIDITRACK_H
