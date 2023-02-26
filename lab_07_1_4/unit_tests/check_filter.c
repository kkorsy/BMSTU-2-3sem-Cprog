#include "check_filter.h"
#include <stdlib.h>
#include "filter.h"
#include "check_main.h"
#include "sort.h"
#include "errors.h"

// Проверка фильтра: обычный тест
START_TEST(test_key_simple)
{
    int pb_src[] = {5, 6, 2, 4, 1};
    int *pe_src = pb_src + 5;
    int *pb_dst = NULL, *pe_dst = NULL;

    int out[] = {5, 6, 4};
    int cr;

    cr = key(pb_src, pe_src, &pb_dst, &pe_dst);
    ck_assert_int_eq(cr, OK);
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
    int *pb_dst = NULL, *pe_dst = NULL;

    int out[] = {2, 1, 3};
    int cr;

    cr = key(pb_src, pe_src, &pb_dst, &pe_dst);
    ck_assert_int_eq(cr, OK);
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
    int *pb_dst = NULL, *pe_dst = NULL;

    int out[] = {5};
    int cr;

    cr = key(pb_src, pe_src, &pb_dst, &pe_dst);
    ck_assert_int_eq(cr, OK);
    cr = array_cmp(pb_dst, pe_dst - pb_dst, out, sizeof(out) / sizeof(out[0]), cmp, sizeof(out[0]));
    ck_assert_int_eq(cr, OK);

    free(pb_dst);
}
END_TEST

// Проверка фильтра: некорректный указатель на начало массива
START_TEST(test_key_bad_beg_ptr)
{
    int *pb_src = NULL;
    int *pe_src = pb_src + 5;
    int *pb_dst = NULL, *pe_dst = NULL;

    int cr;

    cr = key(pb_src, pe_src, &pb_dst, &pe_dst);
    ck_assert_int_eq(cr, PARAM_ERROR);

    free(pb_dst);
}
END_TEST

// Проверка фильтра: некорректный указатель на конец массива
START_TEST(test_key_bad_end_ptr)
{
    int pb_src[] = {1, 2, 3};
    int *pe_src = NULL;
    int *pb_dst = NULL, *pe_dst = NULL;

    int cr;

    cr = key(pb_src, pe_src, &pb_dst, &pe_dst);
    ck_assert_int_eq(cr, PARAM_ERROR);

    free(pb_dst);
}
END_TEST

// Проверка фильтра: указатель на начало больше указателя на конец массива
START_TEST(test_key_pbeg_gt_pend)
{
    int pb_src[] = {1, 2, 3};
    int *pe_src = pb_src - 1;
    int *pb_dst = NULL, *pe_dst = NULL;

    int cr;

    cr = key(pb_src, pe_src, &pb_dst, &pe_dst);
    ck_assert_int_eq(cr, PARAM_ERROR);

    free(pb_dst);
}
END_TEST

// Проверка фильтра: итоговый массив пустой
START_TEST(test_key_res_empty)
{
    int pb_src[] = {1, 1, 1};
    int *pe_src = pb_src + 3;
    int *pb_dst = NULL, *pe_dst = NULL;

    int cr;

    cr = key(pb_src, pe_src, &pb_dst, &pe_dst);
    ck_assert_int_eq(cr, DATA_ERROR);

    free(pb_dst);
}
END_TEST

// Проверка фильтра: указатель на начало совпадает с указателем на конец массива
START_TEST(test_key_empty_array)
{
    int pb_src[] = {1, 2, 3};
    int *pe_src = pb_src;
    int *pb_dst = NULL, *pe_dst = NULL;

    int cr;

    cr = key(pb_src, pe_src, &pb_dst, &pe_dst);
    ck_assert_int_eq(cr, PARAM_ERROR);

    free(pb_dst);
}
END_TEST

// Проверка фильтра: в исходном массиве 1 элемент
START_TEST(test_key_one_elem)
{
    int pb_src[] = { 1 };
    int *pe_src = pb_src + 1;
    int *pb_dst = NULL, *pe_dst = NULL;

    int cr;

    cr = key(pb_src, pe_src, &pb_dst, &pe_dst);
    ck_assert_int_eq(cr, DATA_ERROR);

    free(pb_dst);
}
END_TEST

// Проверка фильтра: указатели на начало и конец исходного массива совпадают с указателями на итоговый массив
START_TEST(test_key_equal_pointers)
{
    int pb_src[] = {5, 4, 3, 2, 1};
    int *pe_src = pb_src + 5;
    int *pb_dst = pb_src, *pe_dst = pe_src;

    int out[] = {5, 4};
    int cr;

    cr = key(pb_src, pe_src, &pb_dst, &pe_dst);
    ck_assert_int_eq(cr, OK);
    cr = array_cmp(pb_dst, pe_dst - pb_dst, out, sizeof(out) / sizeof(out[0]), cmp, sizeof(out[0]));
    ck_assert_int_eq(cr, OK);

    free(pb_dst);
}
END_TEST

Suite* key_suite(Suite *s)
{
    TCase *tc_pos, *tc_neg;

    tc_pos = tcase_create("positives");
    tcase_add_test(tc_pos, test_key_simple);
    tcase_add_test(tc_pos, test_key_res_one_elem);
    tcase_add_test(tc_pos, test_key_zero_avg);
    tcase_add_test(tc_pos, test_key_equal_pointers);

    suite_add_tcase(s, tc_pos);

    tc_neg = tcase_create("negatives");
    tcase_add_test(tc_neg, test_key_bad_beg_ptr);
    tcase_add_test(tc_neg, test_key_bad_end_ptr);
    tcase_add_test(tc_neg, test_key_pbeg_gt_pend);
    tcase_add_test(tc_neg, test_key_res_empty);
    tcase_add_test(tc_neg, test_key_empty_array);
    tcase_add_test(tc_neg, test_key_one_elem);

    suite_add_tcase(s, tc_neg);

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

// Копирование всех элементов
START_TEST(test_copy_all_elems)
{
    int pb_src[] = {1, 2, 3, 4, 5};
    int *pe_src = pb_src + 5;
    int pb_dst[5];
    int res[5] = {1, 2, 3, 4, 5};

    copy(pb_src, pe_src, pb_dst, 0);
    int cr = array_cmp(res, sizeof(res) / sizeof(int), pb_dst, sizeof(pb_dst) / sizeof(int), cmp, sizeof(res[0]));
    ck_assert_int_eq(cr, OK);
}
END_TEST

// Копирование половины элементов
START_TEST(test_copy_half_elems)
{
    int pb_src[] = {1, 2, 3, 4, 5};
    int *pe_src = pb_src + 5;
    int pb_dst[2];
    int res[2] = {4, 5};

    copy(pb_src, pe_src, pb_dst, 3.5);
    int cr = array_cmp(res, sizeof(res) / sizeof(int), pb_dst, sizeof(pb_dst) / sizeof(int), cmp, sizeof(res[0]));
    ck_assert_int_eq(cr, OK);
}
END_TEST

// Копирование неотсортированного массива
START_TEST(test_copy_rand_order)
{
    int pb_src[] = {4, 1, 5, 2, 3};
    int *pe_src = pb_src + 5;
    int pb_dst[3];
    int res[3] = {4, 5, 3};

    copy(pb_src, pe_src, pb_dst, 2);
    int cr = array_cmp(res, sizeof(res) / sizeof(int), pb_dst, sizeof(pb_dst) / sizeof(int), cmp, sizeof(res[0]));
    ck_assert_int_eq(cr, OK);
}
END_TEST

Suite* copy_suite(Suite *s)
{
    TCase *tc_pos;

    tc_pos = tcase_create("positives");
    tcase_add_test(tc_pos, test_copy_all_elems);
    tcase_add_test(tc_pos, test_copy_half_elems);
    tcase_add_test(tc_pos, test_copy_rand_order);

    suite_add_tcase(s, tc_pos);

    return s;
}
