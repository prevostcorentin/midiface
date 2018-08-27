#include "types.h"
#include "errutils.h"



typedef struct {
	int format;
	int header_length;
	int track_chunks_number;
	int division;
} Midifile;


Midifile* __stdcall __declspec(dllexport) midifile_open(const char *filename);
void __stdcall __declspec(dllexport) midifile_dump_header(Midifile *midifile);
void __stdcall __declspec(dllexport) midifile_close(Midifile *midifile);
bool midifile_validate_mthd(byte_t bytes[4]);
