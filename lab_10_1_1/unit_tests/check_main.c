#include "check_node.h"
#include "check_list.h"
#include "check_operations.h"

int main(void)
{
    int no_failed = 0;
    Suite *s;
    SRunner *runner;

    s = suite_create("unit_tests");

    s = data_read_suite(s);
    s = data_init_suite(s);
    s = list_create_suite(s);
    s = list_copy_suite(s);
    s = list_add_end_suite(s);
    s = remove_duplicates_suite(s);
    s = comparator_suite(s);
    s = sorted_insert_suite(s);
    s = sort_suite(s);
    s = insert_suite(s);
    s = find_suite(s);
    s = del_elem_suite(s);
    s = pop_front_suite(s);

    runner = srunner_create(s);

    srunner_run_all(runner, CK_VERBOSE);
    no_failed = srunner_ntests_failed(runner);

    srunner_free(runner);

    return no_failed;
}
