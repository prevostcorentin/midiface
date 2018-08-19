#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MIDIFILE_OK    0x0
#define NOT_MIDIFILE   0x346
#define FILE_NOT_FOUND 0x345

typedef enum {false=0, true=1} bool;
typedef unsigned char byte;

typedef struct {
   byte mthd[4];
   int header_length;
   int format;
   int tracks_number;
   int division;
   // Event *tracks;
} Midifile;


int readint(FILE *fptr, int size);

int midifile_open(Midifile*, const char *filename);
bool midifile_check_mthd(Midifile*);
// void midifile_check_mtrk(Midifile*);
void midifile_dump_header(Midifile*);
void midifile_close(Midifile*);


int main(int argc, char **argv)
{
   if(argc < 2) {
      printf("Usage: %s [filename]\n", argv[0]);
      return EXIT_FAILURE;
   }

   Midifile *midifile;
   int errorcode;
#ifdef DEBUG
   printf("Opening file ...\n");
#endif
   if((errorcode = midifile_open(midifile, argv[1])) != MIDIFILE_OK) {
      printf("error while reading file (0x%x)", errorcode);
      midifile_close(midifile);
      return EXIT_FAILURE;
   }
   midifile_dump_header(midifile);
#ifdef DEBUG
   printf("Closing file ...\n");
#endif
   midifile_close(midifile);

   return EXIT_SUCCESS;
}

int midifile_open(Midifile *midifile, const char *filename)
{
   if(midifile == NULL) {
      midifile = malloc(sizeof(Midifile));
   }
   FILE *fptr;
   if((fptr = fopen(filename, "r")) == NULL) {
      return FILE_NOT_FOUND;
   }
   fread(midifile->mthd, 4, 1, fptr);
   if(!(midifile_check_mthd(midifile))) {
      return NOT_MIDIFILE;
   }
   midifile->header_length = readint(fptr, 4);
   midifile->format = readint(fptr, 2);
   midifile->tracks_number = readint(fptr, 2);
   midifile->division = readint(fptr, 2);
   return MIDIFILE_OK;
}

/*
bool midifile_check_mtrk(Midifile *midifile)
{
   return midifile_compare_header(midifile->mthd, "MTrk");
}
*/

bool _midifile_compare_header(byte bytes[4], const char *header_string)
{
   int i;
   for(i=0; i < 4; i++) {
      if(bytes[i] != header_string[i]) {
         return false;
      }
   }
   return true;
}

bool midifile_check_mthd(Midifile *midifile)
{
   return _midifile_compare_header(midifile->mthd, "MThd");
}

void midifile_dump_header(Midifile *midifile)
{
   printf("format: %d\n"
          "number of tracks: %d\n"
          "division: %d\n",
          midifile->format,
          midifile->tracks_number,
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

int readint(FILE *fptr, int size)
{
   byte bytes[size];
   int value=0;

   fread(bytes, size, 1, fptr);
   for(int i=0; i < size; i++) {
      value = value << 1 | bytes[i];
   }

   return value;
}
