#include "check_operations.h"
#include "item.h"
#include "operations.h"
#include "check_main.h"

// Не нашлось ни одной структуры
START_TEST(test_find_not_found)
{
    struct object items[3] = {{ "aaa", 1, 2 }, { "bbb", 3, 4 }, { "ccc", 5, 6 }};
    size_t n = 3;
    char *substr = "zzz";

    int cr = find(items, n, substr);
    ck_assert_int_eq(cr, FIND_ERROR);
}
END_TEST

// Все структуры подходят под условие
START_TEST(test_find_all_structs)
{
    struct object items[3] = {{ "aaa\n", 1, 2 }, { "abb\n", 3, 4 }, { "aac\n", 5, 6 }};
    size_t n = 3;
    char *substr = "a";

    int cr = find(items, n, substr);
    ck_assert_int_eq(cr, OK);
}
END_TEST

// Обычный тест
START_TEST(test_find_simple)
{
    struct object items[3] = {{ "baa\n", 1, 2 }, { "bba\n", 3, 4 }, { "bac\n", 5, 6 }};
    size_t n = 3;
    char *substr = "ba";

    int cr = find(items, n, substr);
    ck_assert_int_eq(cr, OK);
}
END_TEST

Suite* find_suite(Suite *s)
{
    TCase *tc_neg, *tc_pos;

    tc_neg = tcase_create("negatives");
    tcase_add_test(tc_neg, test_find_not_found);

    suite_add_tcase(s, tc_neg);

    tc_pos = tcase_create("positives");
    tcase_add_test(tc_pos, test_find_all_structs);
    tcase_add_test(tc_pos, test_find_simple);

    suite_add_tcase(s, tc_pos);

    return s;
}

// Результат - 0
START_TEST(test_density_zero)
{
    struct object item = { "aaa", 0, 1 };
    double density_expect = 0;

    double density_res = density(item);
    ck_assert_double_eq(density_res, density_expect);
}
END_TEST

// Обычный тест
START_TEST(test_density_simple)
{
    struct object item = { "aaa", 5, 2 };
    double density_expect = 2.5;

    double density_res = density(item);
    ck_assert_double_eq(density_res, density_expect);
}
END_TEST

Suite* density_suite(Suite *s)
{
    TCase *tc_pos;

    tc_pos = tcase_create("positives");
    tcase_add_test(tc_pos, test_density_zero);
    tcase_add_test(tc_pos, test_density_simple);

    suite_add_tcase(s, tc_pos);

    return s;
}

// Массив уже отсортирован
START_TEST(test_sort_already_sorted)
{
    struct object items[3] = {{ "aaa\n", 1, 2 }, { "bbb\n", 3, 4 }, { "ccc\n", 5, 6 }};
    size_t n = 3;

    struct object items_expect[3] = {{ "aaa\n", 1, 2 }, { "bbb\n", 3, 4 }, { "ccc\n", 5, 6 }};

    sort(items, n);

    check_arr_eq(items, items_expect, n);
}
END_TEST

// Массив отсортирован по убыванию
START_TEST(test_sort_reverse_sorted)
{
    struct object items[4] = {{ "ddd\n", 7, 8 }, { "ccc\n", 5, 6 }, { "bbb\n", 3, 4 }, { "aaa\n", 1, 2 }};
    size_t n = 4;

    struct object items_expect[4] = {{ "aaa\n", 1, 2 }, { "bbb\n", 3, 4 }, { "ccc\n", 5, 6 }, { "ddd\n", 7, 8 }};

    sort(items, n);

    check_arr_eq(items, items_expect, n);
}
END_TEST

// Массив не отсортирован
START_TEST(test_sort_simple)
{
    struct object items[4] = {{ "ccc\n", 5, 6 }, { "aaa\n", 1, 2 }, { "ddd\n", 7, 8 }, { "bbb\n", 3, 4 }};
    size_t n = 4;

    struct object items_expect[4] = {{ "aaa\n", 1, 2 }, { "bbb\n", 3, 4 }, { "ccc\n", 5, 6 }, { "ddd\n", 7, 8 }};

    sort(items, n);

    check_arr_eq(items, items_expect, n);
}
END_TEST

// В массиве 1 элемент
START_TEST(test_sort_one_elem)
{
    struct object items[1] = {{ "aaa\n", 1, 2 }};
    size_t n = 1;

    struct object items_expect[1] = {{ "aaa\n", 1, 2 }};

    sort(items, n);

    check_arr_eq(items, items_expect, n);
}
END_TEST

// Проверка устойчивости сортировки
START_TEST(test_sort_stability)
{
    struct object items[4] = {{ "aaa\n", 5, 6 }, { "bbb\n", 1, 2 }, { "ccc\n", 5, 6 }, { "ddd\n", 1, 2 }};
    size_t n = 4;

    struct object items_expect[4] = {{ "ddd\n", 1, 2 }, { "bbb\n", 1, 2 }, { "aaa\n", 5, 6 }, { "ccc\n", 5, 6 }};

    sort(items, n);

    check_arr_eq(items, items_expect, n);
}
END_TEST

Suite* sort_suite(Suite *s)
{
    TCase *tc_pos;

    tc_pos = tcase_create("positives");
    tcase_add_test(tc_pos, test_sort_already_sorted);
    tcase_add_test(tc_pos, test_sort_reverse_sorted);
    tcase_add_test(tc_pos, test_sort_simple);
    tcase_add_test(tc_pos, test_sort_one_elem);
    tcase_add_test(tc_pos, test_sort_stability);

    suite_add_tcase(s, tc_pos);

    return s;
}
