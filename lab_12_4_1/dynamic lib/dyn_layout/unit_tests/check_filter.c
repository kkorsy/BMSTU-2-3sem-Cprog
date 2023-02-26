#include "check_filter.h"
#include <stdlib.h>
#include "check_main.h"
#include "lib_arr.h"

// Проверка фильтра: обычный тест
START_TEST(test_key_simple)
{
    int pb_src[] = {5, 6, 2, 4, 1};
    int *pe_src = pb_src + 5;
    int *pb_dst = malloc(3 * sizeof(int));
    int *pe_dst = pb_dst + 3;

    int out[] = {5, 6, 4};
    int cr;

    key(pb_src, pe_src, pb_dst, average(pb_src, pe_src));
    cr = array_cmp(pb_dst, pe_dst - pb_dst, out, sizeof(out) / sizeof(out[0]), cmp, sizeof(out[0]));
    ck_assert_int_eq(cr, OK);
    
    free(pb_dst);
}
END_TEST

// Проверка фильтра: среднее арифметическое равно нулю
START_TEST(test_key_zero_avg)
{
    int pb_src[] = {-1, -2, 2, -3, 1, 3};
    int *pe_src = pb_src + 6;
    int *pb_dst = malloc(3 * sizeof(int));
    int *pe_dst = pb_dst + 3;

    int out[] = {2, 1, 3};
    int cr;

    key(pb_src, pe_src, pb_dst, average(pb_src, pe_src));
    cr = array_cmp(pb_dst, pe_dst - pb_dst, out, sizeof(out) / sizeof(out[0]), cmp, sizeof(out[0]));
    ck_assert_int_eq(cr, OK);
    
    free(pb_dst);
}
END_TEST

// Проверка фильтра: в итоговом массиве 1 элемент
START_TEST(test_key_res_one_elem)
{
    int pb_src[] = {1, 1, 1, 1, 5};
    int *pe_src = pb_src + 5;
    int *pb_dst = malloc(sizeof(int));
    int *pe_dst = pb_dst + 1;

    int out[] = {5};
    int cr;

    key(pb_src, pe_src, pb_dst, average(pb_src, pe_src));
    cr = array_cmp(pb_dst, pe_dst - pb_dst, out, sizeof(out) / sizeof(out[0]), cmp, sizeof(out[0]));
    ck_assert_int_eq(cr, OK);

    free(pb_dst);
}
END_TEST

Suite* key_suite(Suite *s)
{
    TCase *tc_pos;

    tc_pos = tcase_create("positives");
    tcase_add_test(tc_pos, test_key_simple);
    tcase_add_test(tc_pos, test_key_res_one_elem);
    tcase_add_test(tc_pos, test_key_zero_avg);

    suite_add_tcase(s, tc_pos);

    return s;
}

// Обычный тест
START_TEST(test_average_simple)
{
    int pb_src[] = {5, 4, 3, 2, 1};
    int *pe_src = pb_src + 5;

    double out = 3, res = average(pb_src, pe_src);
    ck_assert_double_eq(out, res);
}
END_TEST

// Среднее арифметическое равно нулю
START_TEST(test_average_zero)
{
    int pb_src[] = {-1, -2, 3, 2, 1, -3};
    int *pe_src = pb_src + 6;

    double out = 0, res = average(pb_src, pe_src);
    ck_assert_double_eq(out, res);
}
END_TEST

// Один элемент в массиве
START_TEST(test_average_one_elem)
{
    int pb_src[] = { 1 };
    int *pe_src = pb_src + 1;

    double out = 1, res = average(pb_src, pe_src);
    ck_assert_double_eq(out, res);
}
END_TEST

// Все элементы массива одинаковые
START_TEST(test_average_equal_numb)
{
    int pb_src[] = {1, 1, 1, 1, 1};
    int *pe_src = pb_src + 5;

    double out = 1, res = average(pb_src, pe_src);
    ck_assert_double_eq(out, res);
}
END_TEST

Suite* average_suite(Suite *s)
{
    TCase *tc_pos;

    tc_pos = tcase_create("positives");
    tcase_add_test(tc_pos, test_average_simple);
    tcase_add_test(tc_pos, test_average_zero);
    tcase_add_test(tc_pos, test_average_one_elem);
    tcase_add_test(tc_pos, test_average_equal_numb);

    suite_add_tcase(s, tc_pos);

    return s;
}

// Все элементы массива подходят
START_TEST(test_num_count_all_elems)
{
    int pb_src[] = {1, 2, 3, 4, 5};
    int *pe_src = pb_src + 5;

    int out = 5, res = num_count(pb_src, pe_src, 0);
    ck_assert_int_eq(out, res);
}
END_TEST

// Ни один элемент массива не подходит
START_TEST(test_num_count_zero_elems)
{
    int pb_src[] = {1, 2, 3, 4, 5};
    int *pe_src = pb_src + 5;

    int out = 0, res = num_count(pb_src, pe_src, 6);
    ck_assert_int_eq(out, res);
}
END_TEST

// Половина элементов подходит
START_TEST(test_num_count_half_elems)
{
    int pb_src[] = {1, 2, 3, 4, 5};
    int *pe_src = pb_src + 5;

    int out = 2, res = num_count(pb_src, pe_src, 3.5);
    ck_assert_int_eq(out, res);
}
END_TEST

Suite* num_count_suite(Suite *s)
{
    TCase *tc_pos;

    tc_pos = tcase_create("positives");
    tcase_add_test(tc_pos, test_num_count_all_elems);
    tcase_add_test(tc_pos, test_num_count_zero_elems);
    tcase_add_test(tc_pos, test_num_count_half_elems);

    suite_add_tcase(s, tc_pos);

    return s;
}
