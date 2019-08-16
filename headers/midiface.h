#ifndef MIDIFACE_MIDIFACE_H
#define MIDIFACE_MIDIFACE_H

extern "C"
{
    Midifile* midifile_open(const char *filename);
    void midifile_dump_header(Midifile *midifile);
    void midifile_close(Midifile *midifile);
    bool midifile_validate_mthd(byte_t bytes[4]);
};

#endif //MIDIFACE_MIDIFACE_H
