#include <stdio.h>

// Copy memory as int
unsigned int read_unsigned_integer(FILE *file_descriptor, size_t read_size);

size_t secure_fread(char *buffer, size_t size, size_t n, FILE *file_descriptor);

int secure_fseek(FILE *, size_t offset, int whence);
