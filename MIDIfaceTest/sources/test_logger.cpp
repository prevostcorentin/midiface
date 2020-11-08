#include <stdio.h>

#include "../../headers/logger.hpp"


/*
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
*/