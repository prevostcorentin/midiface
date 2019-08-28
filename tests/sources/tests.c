#include <CUnit/Basic.h>
#include "test_midifile.c"
#include "test_memutils.c"

void init_test_suites() {
    init_memutils_suite();
    init_midifile_suite();
}

int main() {
    CU_ErrorCode registry_initialization_error_code = CU_initialize_registry();
    if (CUE_SUCCESS != registry_initialization_error_code) {
        return CU_get_error();
    }
    init_test_suites();
    CU_basic_set_mode(CU_BRM_VERBOSE);
    CU_basic_run_tests();
    return CU_get_error();
}