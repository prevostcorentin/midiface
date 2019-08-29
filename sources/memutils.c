#include <headers/memutils.h>
#include <headers/types.h>


unsigned int read_unsigned_integer(const FILE *file_descriptor, const size_t read_size) {
    byte_t bytes[read_size];
    unsigned int value = 0;

    fread(bytes, read_size, 1, file_descriptor);
    // The most significant byte is the first so the most higher
    // power is at the beginning of the start of the file cursor when
    // reading n bytes.
    unsigned int power = 0;
    for (int i = (int) (read_size) - 1; i >= 0; i--) {
        value = value + (bytes[i] << (power * 8));
        power = power + 1;
    }

   return value;
}
