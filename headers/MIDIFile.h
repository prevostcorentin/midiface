#ifndef MIDIFACE_MIDIFILE_H
#define MIDIFACE_MIDIFILE_H

#include <MIDIHeader.h>
#include <types.h>
#include <errutils.h>

#include <memory>
#include <stdio.h>

namespace MIDI
{
    enum class FileType {
        InMemory, OnDisk
    };

    

    typedef struct {
        Header* header;
        FILE* file;
    } File;

    File* midiface_create_file(FILE*);

    File* midiface_open_file(const char* filename);
    void midiface_close_midifile(File* midifile);
    bool midiface_validate_header(char* bytes);
}

#endif
