#include "item.h"
#include "check_main.h"
#include "check_item.h"
#include "check_item_arr.h"
#include "check_operations.h"

int main(void)
{
    int no_failed = 0;
    Suite *s;
    SRunner *runner;

    s = suite_create("Unit_tests");

    s = item_read_suite(s);
    s = item_init_suite(s);
    s = item_arr_create_suite(s);
    s = item_init_suite(s);
    s = find_suite(s);
    s = density_suite(s);
    s = sort_suite(s);

    runner = srunner_create(s);

    srunner_run_all(runner, CK_VERBOSE);
    no_failed = srunner_ntests_failed(runner);

    srunner_free(runner);

    return no_failed;
}

void check_arr_eq(struct object *items, struct object *items_expect, size_t n)
{
    for (size_t i = 0; i < n; i++)
    {
        ck_assert_str_eq(items[i].name, items_expect[i].name);
        ck_assert_double_eq(items[i].mass, items_expect[i].mass);
        ck_assert_double_eq(items[i].volume, items_expect[i].volume);
    }
}
