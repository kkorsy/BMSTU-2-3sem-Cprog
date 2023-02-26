#include "check_sort.h"
#include "lib_arr.h"
#include "check_main.h"

// Сортировка массива с одним элементом
START_TEST(test_mysort_one_elem)
{
    int a[] = { 1 };
    int out[] = { 1 };
    int cr;

    mysort(a, sizeof(a) / sizeof(a[0]), sizeof(a[0]), cmp);
    cr = array_cmp(a, sizeof(a) / sizeof(a[0]), out, sizeof(out) / sizeof(out[0]), cmp, sizeof(out[0]));
    ck_assert_int_eq(cr, OK);
}
END_TEST

// Сортировка уже отсортированного массива
START_TEST(test_mysort_sorted_array)
{
    int a[] = {1, 2, 3, 4, 5};
    int out[] = {1, 2, 3, 4, 5};
    int cr;

    mysort(a, sizeof(a) / sizeof(a[0]), sizeof(a[0]), cmp);
    cr = array_cmp(a, sizeof(a) / sizeof(a[0]), out, sizeof(out) / sizeof(out[0]), cmp, sizeof(out[0]));
    ck_assert_int_eq(cr, OK);
}
END_TEST

// Сортировка массива отсортированного в обратном порядке
START_TEST(test_mysort_reverse_sorted_array)
{
    int a[] = {5, 4, 3, 2, 1};
    int out[] = {1, 2, 3, 4, 5};
    int cr;

    mysort(a, sizeof(a) / sizeof(a[0]), sizeof(a[0]), cmp);
    cr = array_cmp(a, sizeof(a) / sizeof(a[0]), out, sizeof(out) / sizeof(out[0]), cmp, sizeof(out[0]));
    ck_assert_int_eq(cr, OK);
}
END_TEST

// Сортировка массива, состоящего из одинаковых элементов
START_TEST(test_mysort_equal_elems)
{
    int a[] = {5, 5, 5, 5, 5};
    int out[] = {5, 5, 5, 5, 5};
    int cr;

    mysort(a, sizeof(a) / sizeof(a[0]), sizeof(a[0]), cmp);
    cr = array_cmp(a, sizeof(a) / sizeof(a[0]), out, sizeof(out) / sizeof(out[0]), cmp, sizeof(out[0]));
    ck_assert_int_eq(cr, OK);
}
END_TEST

// Сортировка массива вещественных чисел
START_TEST(test_mysort_double)
{
    double a[] = {4.3, 2.1, 2.4, 1.6, 1.0};
    double out[] = {1.0, 1.6, 2.1, 2.4, 4.3};
    int cr;

    mysort(a, sizeof(a) / sizeof(a[0]), sizeof(a[0]), cmp_double);
    cr = array_cmp(a, sizeof(a) / sizeof(a[0]), out, sizeof(out) / sizeof(out[0]), cmp_double, sizeof(out[0]));
    ck_assert_int_eq(cr, OK);
}
END_TEST

// Сортировка массива символов
START_TEST(test_mysort_char)
{
    char a[] = {'b', 'd', 'a', 'c', 'e'};
    char out[] = {'a', 'b', 'c', 'd', 'e'};
    int cr;

    mysort(a, sizeof(a) / sizeof(a[0]), sizeof(a[0]), cmp_char);
    cr = array_cmp(a, sizeof(a) / sizeof(a[0]), out, sizeof(out) / sizeof(out[0]), cmp_char, sizeof(out[0]));
    ck_assert_int_eq(cr, OK);
}
END_TEST

Suite* mysort_suite(Suite *s)
{
    TCase *tc_pos;

    tc_pos = tcase_create("positives");
    tcase_add_test(tc_pos, test_mysort_one_elem);
    tcase_add_test(tc_pos, test_mysort_sorted_array);
    tcase_add_test(tc_pos, test_mysort_reverse_sorted_array);
    tcase_add_test(tc_pos, test_mysort_equal_elems);
    tcase_add_test(tc_pos, test_mysort_double);
    tcase_add_test(tc_pos, test_mysort_char);

    suite_add_tcase(s, tc_pos);

    return s;
}

// Проверка компаратора: первый элемент больше второго
START_TEST(test_cmp_first_gt_second)
{
    int a = 5, b = 1;
    int cr;

    cr = cmp(&a, &b);
    ck_assert_int_eq(cr, 4);
}
END_TEST

// Проверка компаратора: первый элемент меньше второго
START_TEST(test_cmp_first_lt_second)
{
    int a = 1, b = 5;
    int cr;

    cr = cmp(&a, &b);
    ck_assert_int_eq(cr, -4);
}
END_TEST

// Проверка компаратора: элементы равны
START_TEST(test_cmp_equal)
{
    int a = 1, b = 1;
    int cr;

    cr = cmp(&a, &b);
    ck_assert_int_eq(cr, 0);
}
END_TEST

Suite* cmp_suite(Suite *s)
{
    TCase *tc_pos;

    tc_pos = tcase_create("positives");
    tcase_add_test(tc_pos, test_cmp_first_gt_second);
    tcase_add_test(tc_pos, test_cmp_first_lt_second);
    tcase_add_test(tc_pos, test_cmp_equal);

    suite_add_tcase(s, tc_pos);

    return s;
}

// Перестановка целых чисел
START_TEST(test_swap_int)
{
    int a = 1, b = 2;

    swap(&a, &b, sizeof(int));
    ck_assert_int_eq(b, 1);
    ck_assert_int_eq(a, 2);
}
END_TEST

// Перестановка вещественных чисел
START_TEST(test_swap_double)
{
    double a = 1.1, b = 2.2;

    swap(&a, &b, sizeof(double));
    ck_assert_double_eq(a, 2.2);
    ck_assert_double_eq(b, 1.1);
}
END_TEST

Suite* swap_suite(Suite *s)
{
    TCase *tc_pos;

    tc_pos = tcase_create("positives");
    tcase_add_test(tc_pos, test_swap_int);
    tcase_add_test(tc_pos, test_swap_double);

    suite_add_tcase(s, tc_pos);

    return s;
}