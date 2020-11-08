#ifndef MIDIFACE_MEMUTILS_H
#define MIDIFACE_MEMUTILS_H

#include <cstdio>

// Copy memory as int
unsigned int read_unsigned_integer(FILE *file_descriptor, size_t read_size);
size_t secure_fread(char *buffer, size_t size, size_t n, FILE *file_descriptor);
int secure_fseek(FILE *, size_t offset, int whence);
size_t read_chunk(FILE *file_descriptor, char *bytes);

size_t seek_remind(FILE *file_descriptor, int offset, int whence);

#ifdef _MSC_VER
FILE* fmemopen(char* message, size_t size, char* mode);
#endif

#endif