#include "check_arr_lib.h"
#include "arr_lib.h"

void check_arr(long long unsigned *exp_arr, long long unsigned *arr, int n)
{
    for (int i = 0; i < n; i++)
        ck_assert_int_eq(exp_arr[i], arr[i]);
}

void check_arr_int(int *exp_arr, int *arr, int n)
{
    for (int i = 0; i < n; i++)
        ck_assert_int_eq(exp_arr[i], arr[i]);
}

// Один элемент в массиве
START_TEST(test_ff_one_elem)
{
    long long unsigned arr[1];
    long long unsigned exp_arr[1] = { 0 };
    int n = 1;

    fill_fib(arr, n);

    check_arr(exp_arr, arr, n);
}
END_TEST

// Обычный тест
START_TEST(test_ff_simple)
{
    long long unsigned arr[10];
    long long unsigned exp_arr[10] = { 0, 1, 1, 2, 3, 5, 8, 13, 21, 34 };
    int n = 10;

    fill_fib(arr, n);

    check_arr(exp_arr, arr, n);
}
END_TEST

Suite* fill_fib_suite(Suite *s)
{
    TCase *tc_pos;

    tc_pos = tcase_create("positives");
    tcase_add_test(tc_pos, test_ff_one_elem);
    tcase_add_test(tc_pos, test_ff_simple);

    suite_add_tcase(s, tc_pos);

    return s;
}

// Недостаточный размер массива
START_TEST(test_rm_small_size)
{
    int src[5] = { 1, 2, 3, 4, 5 }, n = 5;
    int dst[1], m = 1;

    ck_assert_int_eq(rm_duplicates(src, n, dst, &m), 1);
}
END_TEST

// В массиве нет повторений
START_TEST(test_rm_no_repeats)
{
    int src[5] = { 1, 2, 3, 4, 5 }, n = 5;
    int dst[5], m = 5;
    int dst_exp[5] = { 1, 2, 3, 4, 5 };

    ck_assert_int_eq(rm_duplicates(src, n, dst, &m), 0);
    check_arr_int(dst_exp, dst, m);
}
END_TEST

// Обычный тест
START_TEST(test_rm_simple)
{
    int src[5] = { 1, 3, 3, 1, 5 }, n = 5;
    int dst[5], m = 5;
    int dst_exp[3] = { 1, 3, 5 };

    ck_assert_int_eq(rm_duplicates(src, n, dst, &m), 0);
    check_arr_int(dst_exp, dst, m);
}
END_TEST

Suite* rm_dupl_suite(Suite *s)
{
    TCase *tc_neg, *tc_pos;

    tc_neg = tcase_create("negatives");
    tcase_add_test(tc_neg, test_rm_small_size);

    suite_add_tcase(s, tc_neg);

    tc_pos = tcase_create("positives");
    tcase_add_test(tc_pos, test_rm_no_repeats);
    tcase_add_test(tc_pos, test_rm_simple);

    suite_add_tcase(s, tc_pos);

    return s;
}
