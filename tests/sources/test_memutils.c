#include <malloc.h>

#include <headers/memutils.h>

void read_int_4_bytes_test() {
    void *data = malloc(sizeof(int));
    const unsigned int source_integer = 0b11111111111111111111111111111111; // 4294967295
    memcpy(data, &source_integer, 4);
    FILE *stream = fmemopen(data, 4, "rb");

    const unsigned int read_integer = read_unsigned_integer(stream, 4);

    CU_ASSERT_EQUAL(read_integer, source_integer);
}

void read_int_3_bytes_test() {
    void *data = malloc(sizeof(int));
    const unsigned int source_integer = 0b111111111111111111111111; // 16777215
    memcpy(data, &source_integer, 3);
    FILE *stream = fmemopen(data, 3, "rb");

    const unsigned int read_integer = read_unsigned_integer(stream, 3);

    CU_ASSERT_EQUAL(read_integer, source_integer);
}

void read_int_2_bytes_test() {
    void *data = malloc(sizeof(int));
    const short unsigned int source_integer = 0b1111111111111111; // 65535
    memcpy(data, &source_integer, 2);
    FILE *stream = fmemopen(data, 2, "rb");

    const unsigned int read_integer = read_unsigned_integer(stream, 2);

    CU_ASSERT_EQUAL(read_integer, source_integer);
}

void read_int_1_byte_test() {
    void *data = malloc(sizeof(int));
    const short unsigned int source_integer = 0b000000011111111; // 127
    memcpy(data, &source_integer, 1);
    FILE *stream = fmemopen(data, 1, "rb");

    const unsigned int read_integer = read_unsigned_integer(stream, 1);

    CU_ASSERT_EQUAL(read_integer, source_integer);
}

void read_int_half_byte_test() {
    void *data = malloc(sizeof(int));
    const short unsigned int source_integer = 0b000000000001111; // 15
    memcpy(data, &source_integer, 1);
    FILE *stream = fmemopen(data, 1, "rb");

    const unsigned int read_integer = read_unsigned_integer(stream, 1);

    CU_ASSERT_EQUAL(read_integer, source_integer);
}

void read_int_quarter_byte_test() {
    void *data = malloc(sizeof(int));
    const short unsigned int source_integer = 0b0000000000000011; // 3
    memcpy(data, &source_integer, 1);
    FILE *stream = fmemopen(data, 1, "rb");

    const unsigned int read_integer = read_unsigned_integer(stream, 1);
    CU_ASSERT_EQUAL(read_integer, source_integer);
}

void read_int_eleven_bit_on_test() {
    void *data = malloc(sizeof(int));
    const short unsigned int source_integer = 0b0000000000000100; // 1024
    memcpy(data, &source_integer, 2);
    FILE *stream = fmemopen(data, 2, "rb");

    const unsigned int read_integer = read_unsigned_integer(stream, 2);

    CU_ASSERT_EQUAL(read_integer, 1024);
}

void init_memutils_suite() {
    CU_pSuite memutils_test_suite = CU_add_suite("Test memory utils", NULL, NULL);
    CU_add_test(memutils_test_suite, "Test read integer of 32 bits",
                read_int_4_bytes_test);
    CU_add_test(memutils_test_suite, "Test read integer of 24 bits",
                read_int_3_bytes_test);
    CU_add_test(memutils_test_suite, "Test read integer of 16 bits",
                read_int_2_bytes_test);
    CU_add_test(memutils_test_suite, "Test read 1024 from 16 bits",
                read_int_eleven_bit_on_test);
    CU_add_test(memutils_test_suite, "Test read integer of 8 bits",
                read_int_1_byte_test);
    CU_add_test(memutils_test_suite, "Test read integer of 4 bits",
                read_int_half_byte_test);
    CU_add_test(memutils_test_suite, "Test read integer of 2 bits",
                read_int_quarter_byte_test);
}