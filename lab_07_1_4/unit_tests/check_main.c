#include "check_main.h"
#include "check_sort.h"
#include "check_filter.h"
#include "errors.h"

#define EPS 1e-06

int main(void)
{
    int no_failed = 0;
    Suite *s;
    SRunner *runner;

    s = suite_create("unit_tests");

    s = mysort_suite(s);
    s = key_suite(s);
    s = cmp_suite(s);
    s = swap_suite(s);
    s = average_suite(s);
    s = num_count_suite(s);
    s = copy_suite(s);

    runner = srunner_create(s);

    srunner_run_all(runner, CK_VERBOSE);
    no_failed = srunner_ntests_failed(runner);

    srunner_free(runner);

    return no_failed;
}

int array_cmp(void *a1, size_t a_n, void *b1, size_t b_n, int (*cmp)(const void *, const void *), size_t s)
{
    char *a = a1, *b = b1;
    if (a_n != b_n)
        return CHECK_ERROR;
    
    for (size_t i = 0; i < a_n; i++)
        if (cmp(a + i * s, b + i * s) != 0)
            return CHECK_ERROR;

    return OK;
}

int cmp_double(const void *pl, const void *pr)
{
    double temp = *(double *)pl - *(double *)pr;
    if (temp > EPS)
        return 1;
    if (temp < -EPS)
        return -1;
    return 0;
}

int cmp_char(const void *pl, const void *pr)
{
    return *(char *)pl - *(char *)pr;
}
