#include "check_operations.h"
#include "operations.h"
#include "check_list.h"
#include <stdlib.h>

// Значение равно нулю
START_TEST(test_calc_zero)
{
    node_t node_4 = { 4, 4, NULL };
    node_t node_3 = { 3, 3, &node_4 };
    node_t node_2 = { 2, 2, &node_3 };
    node_t node_1 = { 1, 1, &node_2 };

    int res = calc(&node_1, 0);
    ck_assert_int_eq(res, 0);
}
END_TEST

// Список пустой
START_TEST(test_calc_empty)
{
    node_t *node_1 = NULL;

    int res = calc(node_1, 1);
    ck_assert_int_eq(res, 0);
}
END_TEST

// Обычный тест
START_TEST(test_calc_simple)
{
    node_t node_4 = { 4, 4, NULL };
    node_t node_3 = { 3, 3, &node_4 };
    node_t node_2 = { 2, 2, &node_3 };
    node_t node_1 = { 1, 1, &node_2 };

    int res = calc(&node_1, 1);
    ck_assert_int_eq(res, 10);
}
END_TEST

Suite* calc_suite(Suite *s)
{
    TCase *tc_pos;

    tc_pos = tcase_create("positives");
    tcase_add_test(tc_pos, test_calc_zero);
    tcase_add_test(tc_pos, test_calc_empty);
    tcase_add_test(tc_pos, test_calc_simple);

    suite_add_tcase(s, tc_pos);

    return s;
}

// Итоговый список пустой
START_TEST(test_ddx_res_empty)
{
    node_t *node_3 = node_create(3, 0);
    node_t *node_2 = node_create(2, 0);
    node_t *node_1 = node_create(1, 0);

    node_3->next = NULL;
    node_2->next = node_3;
    node_1->next = node_2;

    node_1 = derive(node_1);

    ck_assert_ptr_null(node_1);
}
END_TEST

// Список пустой
START_TEST(test_ddx_empty)
{
    node_t *node_1 = NULL;

    node_1 = derive(node_1);

    ck_assert_ptr_null(node_1);
}
END_TEST

// Обычный тест
START_TEST(test_ddx_simple)
{
    node_t node_4 = { 4, 4, NULL };
    node_t node_3 = { 3, 3, &node_4 };
    node_t node_2 = { 2, 2, &node_3 };
    node_t node_1 = { 1, 1, &node_2 };

    derive(&node_1);

    node_t exp_4 = { 16, 3, NULL };
    node_t exp_3 = { 9, 2, &exp_4 };
    node_t exp_2 = { 4, 1, &exp_3 };
    node_t exp_1 = { 1, 0, &exp_2 };

    check_list_eq(&exp_1, &node_1);
}
END_TEST

Suite* derive_suite(Suite *s)
{
    TCase *tc_pos;

    tc_pos = tcase_create("positives");
    tcase_add_test(tc_pos, test_ddx_res_empty);
    tcase_add_test(tc_pos, test_ddx_empty);
    tcase_add_test(tc_pos, test_ddx_simple);

    suite_add_tcase(s, tc_pos);

    return s;
}

// Один список пустой
START_TEST(test_sum_one_empty)
{
    node_t l1_4 = { 4, 4, NULL };
    node_t l1_3 = { 3, 3, &l1_4 };
    node_t l1_2 = { 2, 2, &l1_3 };
    node_t l1_1 = { 1, 1, &l1_2 };

    node_t *l2_1 = NULL;

    node_t exp_4 = { 4, 4, NULL };
    node_t exp_3 = { 3, 3, &exp_4 };
    node_t exp_2 = { 2, 2, &exp_3 };
    node_t exp_1 = { 1, 1, &exp_2 };

    node_t *res = summation(&l1_1, l2_1);
    check_list_eq(res, &exp_1);

    list_free(res);
}
END_TEST

// Обычный тест сложения
START_TEST(test_sum_simple)
{
    node_t l1_4 = { 4, 4, NULL };
    node_t l1_3 = { 3, 3, &l1_4 };
    node_t l1_2 = { 2, 2, &l1_3 };
    node_t l1_1 = { 1, 1, &l1_2 };

    node_t l2_4 = { 5, 4, NULL };
    node_t l2_3 = { 5, 3, &l2_4 };
    node_t l2_2 = { 5, 2, &l2_3 };
    node_t l2_1 = { 5, 1, &l2_2 };

    node_t exp_4 = { 9, 4, NULL };
    node_t exp_3 = { 8, 3, &exp_4 };
    node_t exp_2 = { 7, 2, &exp_3 };
    node_t exp_1 = { 6, 1, &exp_2 };

    node_t *res = summation(&l1_1, &l2_1);
    check_list_eq(res, &exp_1);

    list_free(res);
}
END_TEST

Suite* summation_suite(Suite *s)
{
    TCase *tc_pos;

    tc_pos = tcase_create("positives");
    tcase_add_test(tc_pos, test_sum_one_empty);
    tcase_add_test(tc_pos, test_sum_simple);

    suite_add_tcase(s, tc_pos);

    return s;
}

// Исходный список пустой
START_TEST(test_sep_empty)
{
    node_t *node_1 = NULL;

    node_t *head_even = NULL, *head_odd = NULL;
    separation(node_1, &head_even, &head_odd);

    node_t *odd_1 = NULL;
    node_t *even_1 = NULL;

    check_list_eq(even_1, head_even);
    check_list_eq(odd_1, head_odd);
}
END_TEST

// В списке только нечетные элементы
START_TEST(test_sep_only_odd)
{
    node_t node_4 = { 7, 7, NULL };
    node_t node_3 = { 5, 5, &node_4 };
    node_t node_2 = { 3, 3, &node_3 };
    node_t node_1 = { 1, 1, &node_2 };

    node_t *head_even = NULL, *head_odd = NULL;
    separation(&node_1, &head_even, &head_odd);

    node_t odd_4 = { 7, 7, NULL };
    node_t odd_3 = { 5, 5, &odd_4 };
    node_t odd_2 = { 3, 3, &odd_3 };
    node_t odd_1 = { 1, 1, &odd_2 };

    node_t *even_1 = NULL;

    check_list_eq(even_1, head_even);
    check_list_eq(&odd_1, head_odd);
}
END_TEST

// В списке только четные элементы
START_TEST(test_sep_only_even)
{
    node_t node_4 = { 6, 6, NULL };
    node_t node_3 = { 4, 4, &node_4 };
    node_t node_2 = { 2, 2, &node_3 };
    node_t node_1 = { 0, 0, &node_2 };

    node_t *head_even = NULL, *head_odd = NULL;
    separation(&node_1, &head_even, &head_odd);

    node_t even_4 = { 6, 6, NULL };
    node_t even_3 = { 4, 4, &even_4 };
    node_t even_2 = { 2, 2, &even_3 };
    node_t even_1 = { 0, 0, &even_2 };

    node_t *odd_1 = NULL;

    check_list_eq(&even_1, head_even);
    check_list_eq(odd_1, head_odd);
}
END_TEST

// Обычный тест
START_TEST(test_sep_simple)
{
    node_t node_4 = { 4, 4, NULL };
    node_t node_3 = { 3, 3, &node_4 };
    node_t node_2 = { 2, 2, &node_3 };
    node_t node_1 = { 1, 1, &node_2 };

    node_t *head_even = NULL, *head_odd = NULL;
    separation(&node_1, &head_even, &head_odd);

    node_t even_2 = { 4, 4, NULL };
    node_t even_1 = { 2, 2, &even_2 };

    node_t odd_2 = { 3, 3, NULL };
    node_t odd_1 = { 1, 1, &odd_2 };

    check_list_eq(&even_1, head_even);
    check_list_eq(&odd_1, head_odd);
}
END_TEST

Suite* separation_suite(Suite *s)
{
    TCase *tc_pos;

    tc_pos = tcase_create("positives");
    tcase_add_test(tc_pos, test_sep_empty);
    tcase_add_test(tc_pos, test_sep_only_odd);
    tcase_add_test(tc_pos, test_sep_only_even);
    tcase_add_test(tc_pos, test_sep_simple);

    suite_add_tcase(s, tc_pos);

    return s;
}
