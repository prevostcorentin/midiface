#include <malloc.h>

#include <headers/memutils.h>

void read_int_4_bytes_test() {
    void *data = malloc(sizeof(int));
    const unsigned int source_integer = 0b1111111111111111111111111111111; // 2147483647
    memcpy(data, &source_integer, 4);
    const FILE *stream = fmemopen(data, 4, "rb");

    const int read_integer = readint(stream, 4);

    CU_ASSERT_EQUAL(read_integer, source_integer);
}

void read_int_3_bytes_test() {
    void *data = malloc(sizeof(int));
    const unsigned int source_integer = 0b11111111111111111111111; // 8388607
    memcpy(data, &source_integer, 3);
    const FILE *stream = fmemopen(data, 3, "rb");

    const int read_integer = readint(stream, 3);

    CU_ASSERT_EQUAL(read_integer, source_integer);
}

void read_int_2_bytes_test() {
    void *data = malloc(sizeof(int));
    const short unsigned int source_integer = 0b111111111111111; // 32767
    memcpy(data, &source_integer, 2);
    const FILE *stream = fmemopen(data, 2, "rb");

    const int read_integer = readint(stream, 2);

    CU_ASSERT_EQUAL(read_integer, source_integer);
}

void read_int_1_byte_test() {
    void *data = malloc(sizeof(int));
    const short unsigned int source_integer = 0b000000011111111; // 127
    memcpy(data, &source_integer, 1);
    const FILE *stream = fmemopen(data, 1, "rb");

    const int read_integer = readint(stream, 1);

    CU_ASSERT_EQUAL(read_integer, source_integer);
}

void read_int_half_byte_test() {
    void *data = malloc(sizeof(int));
    const short unsigned int source_integer = 0b000000000001111; // 15
    memcpy(data, &source_integer, 1);
    const FILE *stream = fmemopen(data, 1, "rb");

    const int read_integer = readint(stream, 1);

    CU_ASSERT_EQUAL(read_integer, source_integer);
}

void read_int_quarter_byte_test() {
    void *data = malloc(sizeof(int));
    const short unsigned int source_integer = 0b0000000000000011; // 3
    memcpy(data, &source_integer, 1);
    const FILE *stream = fmemopen(data, 1, "rb");

    const int read_integer = readint(stream, 1);
    CU_ASSERT_EQUAL(read_integer, source_integer);
}

void init_memutils_suite() {
    CU_pSuite memutils_test_suite = CU_add_suite("Test memory utils", NULL, NULL);
    CU_add_test(memutils_test_suite, "Test read integer of 32 bits",
                read_int_4_bytes_test);
    CU_add_test(memutils_test_suite, "Test read integer of 24 bits",
                read_int_3_bytes_test);
    CU_add_test(memutils_test_suite, "Test read integer of 16 bits",
                read_int_2_bytes_test);
    CU_add_test(memutils_test_suite, "Test read integer of 8 bits",
                read_int_1_byte_test);
    CU_add_test(memutils_test_suite, "Test read integer of 4 bits",
                read_int_half_byte_test);
    CU_add_test(memutils_test_suite, "Test read integer of 2 bits",
                read_int_quarter_byte_test);
}