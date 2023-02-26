#include "check_item.h"
#include "item.h"
#include "check_main.h"

// Файл пустой
START_TEST(test_read_empty_file)
{
    FILE *f = fopen("./func_tests/data/empty.txt", "r");
    struct object item;

    int cr = item_read(f, &item);
    ck_assert_int_eq(cr, READ_ERROR);
}
END_TEST

// Некорректные данные в файле
START_TEST(test_read_bad_file)
{
    FILE *f = fopen("./func_tests/data/neg_05_in.txt", "r");
    struct object item;

    int cr = item_read(f, &item);
    ck_assert_int_eq(cr, READ_ERROR);
}
END_TEST

// Некорректная масса
START_TEST(test_read_bad_mass)
{
    FILE *f = fopen("./func_tests/data/neg_09_in.txt", "r");
    struct object item;

    int cr = item_read(f, &item);
    ck_assert_int_eq(cr, DATA_ERROR);
}
END_TEST

// Некорректный объем
START_TEST(test_read_bad_volume)
{
    FILE *f = fopen("./func_tests/data/neg_10_in.txt", "r");
    struct object item;

    int cr = item_read(f, &item);
    ck_assert_int_eq(cr, DATA_ERROR);
}
END_TEST

// Успешное считывание
START_TEST(test_read_simple)
{
    FILE *f = fopen("./func_tests/data/file_in_1.txt", "r");
    struct object item;
    struct object item_expect = { "aaa", 1, 2 };

    int cr = item_read(f, &item);
    ck_assert_int_eq(cr, OK);
    
    check_arr_eq(&item, &item_expect, 1);

    item_free(&item);
}
END_TEST

Suite* item_read_suite(Suite *s)
{
    TCase *tc_neg, *tc_pos;

    tc_neg = tcase_create("negatives");
    tcase_add_test(tc_neg, test_read_empty_file);
    tcase_add_test(tc_neg, test_read_bad_file);
    tcase_add_test(tc_neg, test_read_bad_mass);
    tcase_add_test(tc_neg, test_read_bad_volume);

    suite_add_tcase(s, tc_neg);

    tc_pos = tcase_create("positives");
    tcase_add_test(tc_pos, test_read_simple);

    suite_add_tcase(s, tc_pos);

    return s;
}

// Успешная инициализация
START_TEST(test_init_simple)
{
    struct object item;
    char *s = "abc";
    double mass = 1, volume = 2;

    struct object item_expect = { "abc", 1, 2 };

    int cr = item_init(&item, s, mass, volume);
    ck_assert_int_eq(cr, OK);
    
    check_arr_eq(&item, &item_expect, 1);

    item_free(&item);
}
END_TEST

Suite* item_init_suite(Suite *s)
{
    TCase *tc_pos;

    tc_pos = tcase_create("positives");
    tcase_add_test(tc_pos, test_init_simple);

    suite_add_tcase(s, tc_pos);

    return s;
}
