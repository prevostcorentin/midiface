#include <headers/midifile.h>


int main(int argc, char **argv)
{
   if(argc < 2) {
      printf("Usage: %s [filename]\n", argv[0]);
      return EXIT_FAILURE;
   }

   Midifile *midifile;
   midifile = midifile_open(midifile, argv[1]);
   if(midifile_mthd_valid(midifile) != MIDIFILE_OK) {
      perror("invalid mthd");
      midifile_close(midifile);
      return EXIT_FAILURE;
   }
   midifile_dump_header(midifile);
   printf("Closing file ...\n");
   midifile_close(midifile);

   return EXIT_SUCCESS;
}
