#include "check_node.h"
#include <stdio.h>
#include <stdlib.h>

void data_check_eq(data_t *data, data_t *expect)
{
    ck_assert_int_eq(data->count, expect->count);
    ck_assert_double_eq_tol(data->price, expect->price, 1e-07);
}

// Считывание из пустого файла
START_TEST(test_read_empty)
{
    FILE *f = fopen("./func_tests/data/empty.txt", "r");
    data_t data;

    int rc = data_read(f, &data);
    ck_assert_int_eq(rc, DATA_ERROR);

    fclose(f);
}
END_TEST

// Считывание из файла с некорректными данными
START_TEST(test_read_incorrect)
{
    FILE *f = fopen("./func_tests/data/neg_06_in.txt", "r");
    data_t data;

    int rc = data_read(f, &data);
    ck_assert_int_eq(rc, DATA_ERROR);

    fclose(f);
}
END_TEST

// Обычное считывание
START_TEST(test_read_simple)
{
    FILE *f = fopen("./func_tests/data/file_in_1.txt", "r");
    data_t data;

    data_t data_expect = { 15, 139.99};

    int rc = data_read(f, &data);
    ck_assert_int_eq(rc, OK);

    data_check_eq(&data, &data_expect);

    fclose(f);
}
END_TEST

Suite* data_read_suite(Suite *s)
{
    TCase *tc_neg, *tc_pos;

    tc_neg = tcase_create("negatives");
    tcase_add_test(tc_neg, test_read_empty);
    tcase_add_test(tc_neg, test_read_incorrect);

    suite_add_tcase(s, tc_neg);

    tc_pos = tcase_create("positives");
    tcase_add_test(tc_pos, test_read_simple);

    suite_add_tcase(s, tc_pos);

    return s;
}

// Обычная инициализация
START_TEST(test_init_simple)
{
    data_t data;
    data_t expect = { 10, 52.4};

    data_init(&data, 10, 52.4);

    data_check_eq(&data, &expect);
}
END_TEST

Suite* data_init_suite(Suite *s)
{
    TCase *tc_pos;

    tc_pos = tcase_create("positives");
    tcase_add_test(tc_pos, test_init_simple);

    suite_add_tcase(s, tc_pos);

    return s;
}
