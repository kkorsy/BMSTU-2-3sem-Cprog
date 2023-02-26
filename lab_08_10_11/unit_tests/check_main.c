#include "check_matrix_io.h"
#include "check_matrix_op.h"

int main(void)
{
    int no_failed = 0;
    Suite *s;
    SRunner *runner;

    s = suite_create("unit_tests");

    s = matrix_read_suite(s);
    s = matrix_create_suite(s);
    s = matrix_mult_suite(s);
    s = matrix_sum_suite(s);
    s = find_max_suite(s);
    s = swap_cols_suite(s);
    s = check_zero_line_suite(s);
    s = gauss_solving_suite(s);

    runner = srunner_create(s);

    srunner_run_all(runner, CK_VERBOSE);
    no_failed = srunner_ntests_failed(runner);

    srunner_free(runner);

    return no_failed;
}
