#ifndef MIDIFACE_MIDISPEC_H
#define MIDIFACE_MIDISPEC_H

#define FILE_FORMAT_SINGLE_TRACK 0
#define FILE_FORMAT_SIMULTANEOUS_TRACKS 1
#define FILE_FORMAT_SEQUENTIALLY_INDEPENDANT_TRACKS 2
#define \
    FILE_FORMAT_STRING_DESCRIPTION(FORMAT_NUMBER) \
        ({ \
            FORMAT_NUMBER == FILE_FORMAT_SINGLE_TRACK ? "Single track multi-channel" : \
            FORMAT_NUMBER == FILE_FORMAT_SIMULTANEOUS_TRACKS ? "Simultaneous tracks" : \
            FORMAT_NUMBER == FILE_FORMAT_SEQUENTIALLY_INDEPENDANT_TRACKS ? "Sequentially independant tracks" : \
            "Unknown"; \
        })

#endif //MIDIFACE_MIDISPEC_H
