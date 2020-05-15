#ifdef CMAKE_BUILD
    #include <headers/errutils.hpp>
    #include <headers/logger.hpp>
    #include <headers/memutils.hpp>
    #include <headers/types.hpp>
#else
    #include "../headers/types.hpp"
    #include "../headers/errutils.hpp"
    #include "../headers/logger.hpp"
    #include "../headers/memutils.hpp"
#endif

constexpr auto MAX_INTEGER_SIZE = 32;;

unsigned int read_unsigned_integer(FILE *file_descriptor, const size_t read_size) {
    char bytes[MAX_INTEGER_SIZE];
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
            send_log(LogLevel::MF_INFO, (char*)"End of stream@%p reached", file_descriptor);
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

size_t seek_remind(FILE *file_descriptor, int offset, int whence) {
    size_t last_position = ftell(file_descriptor);
    secure_fseek(file_descriptor, offset, whence);
    return last_position;
}