#include <CUnit/Basic.h>
#include "test_midifile.c"
#include "test_midistream.c"
#include "test_memutils.c"
#include "test_logger.c"

#include <headers/errutils.h>

void init_test_suites() {
    init_memutils_suite();
    init_midifile_suite();
    init_midistream_suite();
    init_logger_suite();
}

int main(int argc, char **argv) {
    CU_ErrorCode registry_initialization_error_code = CU_initialize_registry();
    if (CUE_SUCCESS != registry_initialization_error_code) {
        return CU_get_error();
    }
    init_test_suites();
    CU_basic_set_mode(CU_BRM_VERBOSE);
    midiface_turn_off_quit_on_fatal();
    if (argc > 1) {
        const char* suite_name = argv[1];
        CU_pSuite test_suite = CU_get_suite(suite_name);
        if (argc == 2) {
            CU_basic_run_suite(test_suite);
        } else {
            CU_pSuite chosen_tests_suite = CU_add_suite(test_suite->pName, NULL, NULL);
            for(int i=2; i < argc; i++) {
                char* test_name = argv[i];
                CU_pTest test_to_run = CU_get_test(test_suite, test_name);
                CU_add_test(chosen_tests_suite, test_to_run->pName,
                            test_to_run->pTestFunc);
            }
            CU_basic_run_suite(chosen_tests_suite);
        }
    } else {
        CU_basic_run_tests();
    }
    return CU_get_error();
}