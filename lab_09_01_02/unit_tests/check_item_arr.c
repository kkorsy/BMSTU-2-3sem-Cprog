#include "check_item_arr.h"
#include "item_arr.h"
#include "check_main.h"

// Некорректные данные в файле
START_TEST(test_create_bad_file)
{
    FILE *f = fopen("./func_tests/data/neg_05_in.txt", "r");
    size_t n;
    struct object *items;

    int cr = item_arr_create(f, &items, &n);
    ck_assert_int_eq(cr, READ_ERROR);
}
END_TEST

// Количество элементов - 0
START_TEST(test_create_empty_file)
{
    FILE *f = fopen("./func_tests/data/empty.txt", "r");
    size_t n;
    struct object *items;

    int cr = item_arr_create(f, &items, &n);
    ck_assert_int_eq(cr, DATA_ERROR);
    ck_assert_uint_eq(n, 0);
}
END_TEST

// Успешное создание массива
START_TEST(test_create_simple)
{
    FILE *f = fopen("./func_tests/data/file_in_1.txt", "r");
    size_t n;
    struct object *items;
    struct object items_expect[3] = {{ "aaa", 1, 2 }, { "bbb", 5, 6 }, { "ccc", 7, 8 }};

    int cr = item_arr_create(f, &items, &n);
    ck_assert_int_eq(cr, OK);
    ck_assert_uint_eq(n, 3);
    
    check_arr_eq(items, items_expect, n);

    item_arr_free(items, n);
}
END_TEST

Suite* item_arr_create_suite(Suite *s)
{
    TCase *tc_neg, *tc_pos;

    tc_neg = tcase_create("negatives");
    tcase_add_test(tc_neg, test_create_bad_file);
    tcase_add_test(tc_neg, test_create_empty_file);

    suite_add_tcase(s, tc_neg);

    tc_pos = tcase_create("positives");
    tcase_add_test(tc_pos, test_create_simple);

    suite_add_tcase(s, tc_pos);

    return s;
}

// Некорректные данные в файле
START_TEST(test_count_bad_file)
{
    FILE *f = fopen("./func_tests/data/neg_05_in.txt", "r");
    size_t n;

    int cr = items_count(f, &n);
    ck_assert_int_eq(cr, DATA_ERROR);
    ck_assert_uint_eq(n, 0);
}
END_TEST

// Количество элементов - 0
START_TEST(test_count_zero_items)
{
    FILE *f = fopen("./func_tests/data/empty.txt", "r");
    size_t n;

    int cr = items_count(f, &n);
    ck_assert_int_eq(cr, OK);
    ck_assert_uint_eq(n, 0);
}
END_TEST

// Количество элементов - 3
START_TEST(test_count_simple)
{
    FILE *f = fopen("./func_tests/data/file_in_1.txt", "r");
    size_t n;

    int cr = items_count(f, &n);
    ck_assert_int_eq(cr, OK);
    ck_assert_uint_eq(n, 3);
}
END_TEST

Suite* items_count_suite(Suite *s)
{
    TCase *tc_neg, *tc_pos;

    tc_neg = tcase_create("negatives");
    tcase_add_test(tc_neg, test_count_bad_file);
    tcase_add_test(tc_neg, test_count_zero_items);

    suite_add_tcase(s, tc_neg);

    tc_pos = tcase_create("positives");
    tcase_add_test(tc_pos, test_count_simple);

    suite_add_tcase(s, tc_pos);

    return s;
}
