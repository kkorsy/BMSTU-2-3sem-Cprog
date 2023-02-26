#include "check_node.h"
#include "check_list.h"
#include "check_operations.h"

int main(void)
{
    int no_failed = 0;
    Suite *s;
    SRunner *runner;

    s = suite_create("unit_tests");

    s = add_tail_suite(s);
    s = copy_suite(s);
    s = del_suite(s);
    s = find_prev_suite(s);
    s = node_create_suite(s);
    s = calc_suite(s);
    s = derive_suite(s);
    s = summation_suite(s);
    s = separation_suite(s);

    runner = srunner_create(s);

    srunner_run_all(runner, CK_VERBOSE);
    no_failed = srunner_ntests_failed(runner);

    srunner_free(runner);

    return no_failed;
}
