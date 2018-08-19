#include <headers/memutils.h>
#include <headers/types.h>


int readint(FILE *fptr, int size)
{
   byte_t bytes[size];
   int value=0;

   fread(bytes, size, 1, fptr);
   for(int i=0; i < size; i++) {
      value = value << 1 | bytes[i];
   }

   return value;
}
