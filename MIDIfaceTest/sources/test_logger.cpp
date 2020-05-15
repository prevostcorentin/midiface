#include <stdio.h>

#include "../../headers/logger.h"


void logger_send_debug_log() {
    char message[64];
    FILE *log_stream = fmemopen(message, 64, "w+");
    char written_message[13];
    memset(written_message, 0x00, 13);

    add_log_output(log_stream, DEBUG);
    send_log(DEBUG, "%s", "test");

    rewind(log_stream);
    memset(written_message, 0x00, 13);
    fread(written_message, 12, 1, log_stream);
    CU_ASSERT_STRING_EQUAL(written_message, "DEBUG: test\n");

    clear_logs_stream();
}

void logger_send_error_log() {
    char message[64];
    FILE *log_stream = fmemopen(message, 64, "w+");
    char written_message[13];
    memset(written_message, 0x00, 13);

    add_log_output(log_stream, ERROR);
    send_log(ERROR, "%s", "test");

    rewind(log_stream);
    memset(written_message, 0x00, 13);
    fread(written_message, 12, 1, log_stream);
    CU_ASSERT_STRING_EQUAL(written_message, "ERROR: test\n");

    clear_logs_stream();
}

void logger_send_info_log() {
    char message[64];
    FILE *log_stream = fmemopen(message, 64, "w+");
    char written_message[13];
    memset(written_message, 0x00, 13);

    add_log_output(log_stream, INFO);
    send_log(INFO, "%s", "test");

    rewind(log_stream);
    memset(written_message, 0x00, 13);
    fread(written_message, 12, 1, log_stream);
    CU_ASSERT_STRING_EQUAL(written_message, "INFO: test\n");

    clear_logs_stream();
}

void logger_send_leveled_log_error() {
    char message[64];
    FILE *log_stream = fmemopen(message, 64, "w+");
    char written_message[13];
    memset(written_message, 0x00, 13);

    add_log_output(log_stream, ERROR);

    send_log(DEBUG, "%s", "test");
    rewind(log_stream);
    memset(written_message, 0x00, 13);
    fread(written_message, 12, 1, log_stream);
    CU_ASSERT_STRING_NOT_EQUAL(written_message, "DEBUG: test\n");

    send_log(INFO, "%s", "test");
    rewind(log_stream);
    memset(written_message, 0x00, 13);
    fread(written_message, 11, 1, log_stream);
    CU_ASSERT_STRING_NOT_EQUAL(written_message, "INFO: test\n");

    send_log(ERROR, "%s", "test");
    rewind(log_stream);
    memset(written_message, 0x00, 13);
    fread(written_message, 12, 1, log_stream);
    CU_ASSERT_STRING_EQUAL(written_message, "ERROR: test\n");

    clear_logs_stream();
}

void logger_send_leveled_log_info() {
    char message[64];
    FILE *log_stream = fmemopen(message, 64, "w+");
    char written_message[13];
    memset(written_message, 0x00, 13);

    add_log_output(log_stream, INFO);

    send_log(DEBUG, "%s", "test");
    rewind(log_stream);
    memset(written_message, 0x00, 13);
    fread(written_message, 12, 1, log_stream);
    CU_ASSERT_STRING_NOT_EQUAL(written_message, "DEBUG: test\n");

    send_log(INFO, "%s", "test");
    rewind(log_stream);
    memset(written_message, 0x00, 13);
    fread(written_message, 11, 1, log_stream);
    CU_ASSERT_STRING_EQUAL(written_message, "INFO: test\n");

    send_log(ERROR, "%s", "test");
    fseek(log_stream, -12, SEEK_CUR);
    memset(written_message, 0x00, 13);
    fread(written_message, 12, 1, log_stream);
    CU_ASSERT_STRING_EQUAL(written_message, "ERROR: test\n");

    clear_logs_stream();
}

void logger_send_leveled_log_debug() {
    char message[64];
    FILE *log_stream = fmemopen(message, 64, "w+");
    char written_message[13];
    memset(written_message, 0x00, 13);

    add_log_output(log_stream, DEBUG);

    send_log(DEBUG, "%s", "test");
    rewind(log_stream);
    fread(written_message, 12, 1, log_stream);
    CU_ASSERT_STRING_EQUAL(written_message, "DEBUG: test\n");

    send_log(INFO, "%s", "test");
    fseek(log_stream, -11, SEEK_CUR);
    memset(written_message, 0x00, 13);
    fread(written_message, 11, 1, log_stream);
    CU_ASSERT_STRING_EQUAL(written_message, "INFO: test\n");

    send_log(ERROR, "%s", "test");
    fseek(log_stream, -12, SEEK_CUR);
    memset(written_message, 0x00, 13);
    fread(written_message, 12, 1, log_stream);
    CU_ASSERT_STRING_EQUAL(written_message, "ERROR: test\n");

    clear_logs_stream();
}

void logger_send_multiple_outputs() {
    char message1[64], message2[64];
    FILE *log_stream1 = fmemopen(message1, 64, "w+");
    FILE *log_stream2 = fmemopen(message2, 64, "w+");
    char written_message[13];
    memset(written_message, 0x00, 13);

    add_log_output(log_stream1, DEBUG);
    add_log_output(log_stream2, DEBUG);
    send_log(DEBUG, "%s", "test");

    rewind(log_stream1);
    memset(written_message, 0x00, 13);
    fread(written_message, 11, 1, log_stream1);
    CU_ASSERT_STRING_EQUAL(written_message, "DEBUG: test");
    rewind(log_stream2);
    memset(written_message, 0x00, 13);
    fread(written_message, 11, 1, log_stream2);
    CU_ASSERT_STRING_EQUAL(written_message, "DEBUG: test");

    clear_logs_stream();
}

void init_logger_suite() {
    CU_pSuite logger_test_suite = CU_add_suite("Test logger", NULL, NULL);
    CU_add_test(logger_test_suite, "Test that a log with level DEBUG is sent to the output",
                logger_send_debug_log);
    CU_add_test(logger_test_suite, "Test that log with level ERROR is sent to the output",
                logger_send_error_log);
    CU_add_test(logger_test_suite, "Test that a log with level INFO is sent to the output",
                logger_send_info_log);
    CU_add_test(logger_test_suite, "Test that a stream of level ERROR discards INFO and DEBUG",
                logger_send_leveled_log_error);
    CU_add_test(logger_test_suite, "Test that a stream of level INFO discards DEBUG",
                logger_send_leveled_log_info);
    CU_add_test(logger_test_suite, "Test that a stream of level DEBUG discards nothing",
                logger_send_leveled_log_debug);
    CU_add_test(logger_test_suite, "Test that a log is sent to multiple outputs",
                logger_send_multiple_outputs);
}
