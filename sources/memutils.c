#include <headers/memutils.h>
#include <headers/types.h>


unsigned int read_unsigned_integer(const FILE *file_descriptor, const size_t read_size) {
    byte_t bytes[read_size];
    unsigned int value = 0;

    fread(bytes, read_size, 1, file_descriptor);
    for (unsigned int power = 0; power < read_size; power++) {
        value = value + (bytes[power] << (power * 8));
   }

   return value;
}
