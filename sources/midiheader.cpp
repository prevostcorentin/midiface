#ifdef CMAKE_BUILD
    #include <headers/errutils.hpp>
    #include <headers/memutils.hpp>
    #include <headers/midiheader.hpp>
    #include <headers/types.hpp>
#else
    #include "../headers/errutils.hpp"
    #include "../headers/memutils.hpp"
    #include "../headers/midiheader.hpp"
    #include "../headers/types.hpp"
#endif

#include <malloc.h>
#include <string.h>

bool _validate_mthd(char *bytes) {
    static const unsigned char mthd[] = {0x4d, 0x54, 0x68, 0x64};
    return memcmp(bytes, mthd, sizeof mthd) == 0;
}

MIDIHeader *midiface_read_header(FILE *file_descriptor) {
    secure_fseek(file_descriptor, 0, SEEK_SET);
    char mthd[4];
    read_chunk(file_descriptor, mthd);
    if (!_validate_mthd(mthd)) {
        midiface_throw_error(WRONG_MTHD);
    }
    MIDIHeader *header = (MIDIHeader*)malloc(sizeof(MIDIHeader));
    header->length = read_unsigned_integer(file_descriptor, 4);
    header->format = read_unsigned_integer(file_descriptor, 2);
    header->ntracks = read_unsigned_integer(file_descriptor, 2);
    header->division = read_unsigned_integer(file_descriptor, 2);
    return header;
}

