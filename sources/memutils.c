#include <headers/errutils.h>
#include <headers/logger.h>
#include <headers/memutils.h>
#include <headers/types.h>


unsigned int read_unsigned_integer(FILE *file_descriptor, const size_t read_size) {
    byte_t bytes[read_size];
    unsigned int value = 0;

    secure_fread(bytes, sizeof(char), read_size, file_descriptor);
    // The most significant byte is the first so the most higher
    // power is at the beginning of the file cursor when
    // reading.
    unsigned int power = 0;
    for (int i = (int) (read_size) - 1; i >= 0; i--) {
        value = value + (bytes[i] << (power * 8));
        power = power + 1;
    }

    return value;
}

size_t secure_fread(char *buffer, const size_t size, const size_t n, FILE *file_descriptor) {
    size_t read_size = fread(buffer, size, n, file_descriptor);
    if (size * n != read_size) {
        if (feof(file_descriptor)) {
            send_log(INFO, "End of stream@%p reached", file_descriptor);
        } else {
            midiface_throw_error(READ_EXCEPTION);
        }
    }
    return read_size;
}

int secure_fseek(FILE *file_descriptor, size_t offset, int whence) {
    const int result = fseek(file_descriptor, offset, whence);
    if (result != 0) {
        midiface_throw_error(READ_EXCEPTION);
    }
    return result;
}

size_t read_chunk(FILE *file_descriptor, char *bytes) {
    return secure_fread(bytes, 1, 4, file_descriptor);
}