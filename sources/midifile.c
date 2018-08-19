#include <headers/midifile.h>
#include <headers/memutils.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>


int midifile_open(Midifile *midifile, const char *filename)
{
   FILE *fptr;
   byte_t mthd[4];
   if(midifile == NULL) {
      midifile = malloc(sizeof(Midifile));
   }
   if((fptr = fopen(filename, "r")) == NULL) {
      return FILE_NOT_FOUND;
   }
   fread(mthd, 4, 1, fptr);
   if(!(midifile_validate_mthd(mthd))) {
      return WRONG_MTHD;
   }
   midifile->header_length = readint(fptr, 4);
   midifile->format = readint(fptr, 2);
   midifile->track_chunks_number = readint(fptr, 2);
   midifile->division = readint(fptr, 2);
   return MIDIFILE_OK;
}

/*
bool midifile_check_mtrk(Midifile *midifile)
{
   return midifile_compare_header(midifile->mthd, "MTrk");
}
*/


bool midifile_validate_mthd(byte_t bytes[4])
{
   static const unsigned char mthd[]={ 0x4d, 0x54, 0x68, 0x64 };
   return memcmp(bytes, mthd, sizeof mthd) == 0;

}

void midifile_dump_header(Midifile *midifile)
{
   printf("format: %d\n"
          "number of tracks: %d\n"
          "division: %d\n",
          midifile->format,
          midifile->track_chunks_number,
          midifile->division);
}

void midifile_close(Midifile *midifile)
{
   /*
   if(midifile->tracks != NULL) {
      free(midifile->tracks);
   }
   */
   free(midifile);
}
