#include "types.h"

#define FATAL 0x10000000
#define MIDIFILE_OK 0x00000001
#define WRONG_MTHD  0x00000002
#define FILE_NOT_FOUND 0x00000003


typedef struct {
	int format;
	int header_length;
	int track_chunks_number;
	int division;
} Midifile;


int __stdcall __declspec(dllexport) midifile_open(Midifile *midifile, const char *filename);
void __stdcall __declspec(dllexport) midifile_dump_header(Midifile *midifile);
void __stdcall __declspec(dllexport) midifile_close(Midifile *midifile);
bool midifile_validate_mthd(byte_t bytes[4]);
