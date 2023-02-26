#include "check_str.h"
#include "check_snprintf.h"

int main(void)
{
    int no_failed = 0;
    Suite *s;
    SRunner *runner;

    s = suite_create("unit_tests");

    s = write_str_suite(s);
    s = write_oct_suite(s);
    s = int_to_char_suite(s);
    s = num_len_suite(s);
    s = convert_to_oct_suite(s);
    s = my_snprintf_suite(s);

    runner = srunner_create(s);

    srunner_run_all(runner, CK_VERBOSE);
    no_failed = srunner_ntests_failed(runner);

    srunner_free(runner);

    return no_failed;
}