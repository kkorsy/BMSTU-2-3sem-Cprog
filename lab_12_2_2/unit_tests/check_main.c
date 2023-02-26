#include "check_arr_lib.h"

int main(void)
{
    int no_failed = 0;
    Suite *s;
    SRunner *runner;

    s = suite_create("unit_tests");

    s = fill_fib_suite(s);
    s = rm_dupl_suite(s);

    runner = srunner_create(s);

    srunner_run_all(runner, CK_VERBOSE);
    no_failed = srunner_ntests_failed(runner);

    srunner_free(runner);

    return no_failed;
}