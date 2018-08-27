#include <headers/midifile.h>
#include <stdio.h>
#include <stdlib.h>


int main(int argc, char **argv)
{
   Midifile midifile;
   int errorcode;

   if(argc < 2) {
      printf("Usage: %s [filename]\n", argv[0]);
      return EXIT_FAILURE;
   }
   if((errorcode = midifile_open(&midifile, argv[1])) != MIDIFILE_OK) {
      printf("invalid file (0x%x)", errorcode);
      // midifile_close(midifile);
      return EXIT_FAILURE;
   }
   printf("format: %d\n"
          "number of tracks: %d\n"
          "division: %d\n",
          midifile.format,
          midifile.track_chunks_number,
          midifile.division);
   // midifile_close(&midifile);

   return EXIT_SUCCESS;
}
