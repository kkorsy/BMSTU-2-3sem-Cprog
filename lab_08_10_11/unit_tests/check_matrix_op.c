#include <stdlib.h>
#include "check_matrix_op.h"
#include "matrix_op.h"
#include "matrix_alloc.h"
#include "check_matrix_io.h"

#define EPS 1e-06

void check_int_array(int *data, int *data_expect, size_t n)
{
    for (size_t i = 0; i < n; i++)
        ck_assert_int_eq(data[i], data_expect[i]);
}

// Умножение матриц некорректных размеров
START_TEST(test_matrix_mult_bad_sizes)
{
    double a[2][3] = {{1, 2, 3}, {4, 5, 6}};
    double b[3][2] = {{1, 2}, {3, 4}, {5, 6}};
    
    double* a_pointers[2] = {a[0], a[1]};
    double* b_pointers[3] = {b[0], b[1], b[2]};

    double **c;
    size_t a_n = 2, a_m = 3, b_n = 2, b_m = 3, c_n, c_m;

    int cr = matrix_mult(a_pointers, a_n, a_m, b_pointers, b_n, b_m, &c, &c_n, &c_m);

    ck_assert_int_eq(cr, MATRIX_SIZE_ERROR);
}
END_TEST

// Умножение матриц: обычный тест
START_TEST(test_matrix_mult_correct)
{
    size_t a_n = 2, a_m = 3, b_n = 3, b_m = 2, c_n, c_m;

    double a[2][3] = {{1, 2, 3}, {4, 5, 6}};
    double b[3][2] = {{1, 2}, {3, 4}, {5, 6}};
    double c_exp[2][2] = {{22, 28}, {49, 64}}; 
    
    double* a_pointers[2] = {a[0], a[1]};
    double* b_pointers[3] = {b[0], b[1], b[2]};
    double* c_expect[2] = { c_exp[0], c_exp[1] };

    double **c;
    int cr = matrix_mult(a_pointers, a_n, a_m, b_pointers, b_n, b_m, &c, &c_n, &c_m);
    ck_assert_int_eq(cr, OK);

    check_values(c, c_expect, c_n, c_m);

    matrix_free(c, c_n);
}
END_TEST

// Умножение матриц 1x1
START_TEST(test_matrix_mult_one_elem)
{
    size_t a_n = 1, a_m = 1, b_n = 1, b_m = 1, c_n, c_m;

    double a[1][1] = { {2} };
    double b[1][1] = { {4} };
    double c_exp[1][1] = { {8} }; 
    
    double* a_pointers[1] = { a[0] };
    double* b_pointers[1] = { b[0] };
    double* c_expect[1] = { c_exp[0] };

    double **c;
    int cr = matrix_mult(a_pointers, a_n, a_m, b_pointers, b_n, b_m, &c, &c_n, &c_m);
    ck_assert_int_eq(cr, OK);

    check_values(c, c_expect, c_n, c_m);

    matrix_free(c, c_n);
}
END_TEST

Suite* matrix_mult_suite(Suite *s)
{
    TCase *tc_neg, *tc_pos;

    tc_neg = tcase_create("negatives");
    tcase_add_test(tc_neg, test_matrix_mult_bad_sizes);

    suite_add_tcase(s, tc_neg);

    tc_pos = tcase_create("positives");
    tcase_add_test(tc_pos, test_matrix_mult_correct);
    tcase_add_test(tc_pos, test_matrix_mult_one_elem);

    suite_add_tcase(s, tc_pos);

    return s;
}

// Сложение матриц некорректных размеров
START_TEST(test_matrix_sum_bad_sizes)
{
    double a[2][3] = {{1, 2, 3}, {4, 5, 6}};
    double b[3][2] = {{1, 2}, {3, 4}, {5, 6}}; 
    
    double* a_pointers[2] = {a[0], a[1]};
    double* b_pointers[3] = {b[0], b[1], b[2]};

    double **c;
    size_t a_n = 2, a_m = 3, b_n = 3, b_m = 2, c_n, c_m;

    int cr = matrix_sum(a_pointers, a_n, a_m, b_pointers, b_n, b_m, &c, &c_n, &c_m);

    ck_assert_int_eq(cr, MATRIX_SIZE_ERROR);
}
END_TEST

// Сложение матриц: обычный тест
START_TEST(test_matrix_sum_correct)
{
    size_t a_n = 2, a_m = 3, b_n = 2, b_m = 3, c_n, c_m;

    double a[2][3] = {{1, 2, 3}, {4, 5, 6}};
    double b[2][3] = {{1, 2, 3}, {4, 5, 6}};
    double c_exp[2][3] = {{2, 4, 6}, {8, 10, 12}}; 
    
    double* a_pointers[2] = {a[0], a[1]};
    double* b_pointers[2] = {b[0], b[1]};
    double* c_expect[2] = {c_exp[0], c_exp[1]};

    double **c;
    int cr = matrix_sum(a_pointers, a_n, a_m, b_pointers, b_n, b_m, &c, &c_n, &c_m);
    ck_assert_int_eq(cr, OK);

    check_values(c, c_expect, c_n, c_m);

    matrix_free(c, c_n);
}
END_TEST

// Сложение матриц 1x1
START_TEST(test_matrix_sum_one_elem)
{
    size_t a_n = 1, a_m = 1, b_n = 1, b_m = 1, c_n, c_m;

    double a[1][1] = { {2} };
    double b[1][1] = { {4} };
    double c_exp[1][1] = { {6} }; 
    
    double* a_pointers[1] = { a[0] };
    double* b_pointers[1] = { b[0] };
    double* c_expect[1] = { c_exp[0] };

    double **c;
    int cr = matrix_sum(a_pointers, a_n, a_m, b_pointers, b_n, b_m, &c, &c_n, &c_m);
    ck_assert_int_eq(cr, OK);

    check_values(c, c_expect, c_n, c_m);

    matrix_free(c, c_n);
}
END_TEST

Suite* matrix_sum_suite(Suite *s)
{
    TCase *tc_neg, *tc_pos;

    tc_neg = tcase_create("negatives");
    tcase_add_test(tc_neg, test_matrix_sum_bad_sizes);

    suite_add_tcase(s, tc_neg);

    tc_pos = tcase_create("positives");
    tcase_add_test(tc_pos, test_matrix_sum_correct);
    tcase_add_test(tc_pos, test_matrix_sum_one_elem);

    suite_add_tcase(s, tc_pos);

    return s;
}

// Поиск максимума: обычный тест
START_TEST(test_find_max_simple)
{
    double a[] = {1, 2, 3, 4};
    int max_expect = 3;
    int max = find_max(a, sizeof(a) / sizeof(double), 0);

    ck_assert_int_eq(max, max_expect);
}
END_TEST

// Поиск максимума: начало поиска не с начала массива
START_TEST(test_find_max_start)
{
    double a[] = {4, 3, 2, 1};
    int max_expect = 1;
    int max = find_max(a, sizeof(a) / sizeof(double), 1);

    ck_assert_int_eq(max, max_expect);
}
END_TEST

// Поиск максимума: все элементы одинаковые
START_TEST(test_find_max_eq_elems)
{
    double a[] = {4, 4, 4, 4};
    int max_expect = 0;
    int max = find_max(a, sizeof(a) / sizeof(double), 0);

    ck_assert_int_eq(max, max_expect);
}
END_TEST

Suite* find_max_suite(Suite *s)
{
    TCase *tc_pos;

    tc_pos = tcase_create("positives");
    tcase_add_test(tc_pos, test_find_max_simple);
    tcase_add_test(tc_pos, test_find_max_start);
    tcase_add_test(tc_pos, test_find_max_eq_elems);

    suite_add_tcase(s, tc_pos);

    return s;
}

// Поменять столбцы местами: длина столбца - 1
START_TEST(test_swap_cols_one_row)
{
    int index[2] = {0, 1};
    int index_expect[2] = {1, 0};

    double d[1][2] = {{1, 2}};
    double dexp[1][2] = {{2, 1}};
    double *data[1] = { d[0] };
    double *data_expect[1] = { dexp[0] };

    swap_cols(data, index, 1, 0, 1);
    
    check_values(data, data_expect, 1, 2);
    check_int_array(index, index_expect, 2);
}
END_TEST

// Поменять столбцы местами: обычный тест
START_TEST(test_swap_cols_simple)
{
    int index[4] = {0, 1, 2, 3};
    int index_expect[4] = {0, 3, 2, 1};

    double d[3][4] = {{1, 2, 3, 4}, {5, 6, 7, 8}, {9, 10, 11, 12}};
    double dexp[3][4] = {{1, 4, 3, 2}, {5, 8, 7, 6}, {9, 12, 11, 10}};
    double *data[3] = {d[0], d[1], d[2]};
    double *data_expect[3] = {dexp[0], dexp[1], dexp[2]};

    swap_cols(data, index, 3, 1, 3);
    
    check_values(data, data_expect, 3, 4);
    check_int_array(index, index_expect, 4);
}
END_TEST

// Поменять столбцы местами: индексы столбцов равны
START_TEST(test_swap_cols_same_col)
{
    int index[4] = {0, 1, 2, 3};
    int index_expect[4] = {0, 1, 2, 3};

    double d[3][4] = {{1, 2, 3, 4}, {5, 6, 7, 8}, {9, 10, 11, 12}};
    double dexp[3][4] = {{1, 2, 3, 4}, {5, 6, 7, 8}, {9, 10, 11, 12}};
    double *data[3] = {d[0], d[1], d[2]};
    double *data_expect[3] = {dexp[0], dexp[1], dexp[2]};

    swap_cols(data, index, 3, 2, 2);
    
    check_values(data, data_expect, 3, 4);
    check_int_array(index, index_expect, 4);
}
END_TEST

Suite* swap_cols_suite(Suite *s)
{
    TCase *tc_pos;

    tc_pos = tcase_create("positives");
    tcase_add_test(tc_pos, test_swap_cols_one_row);
    tcase_add_test(tc_pos, test_swap_cols_simple);
    tcase_add_test(tc_pos, test_swap_cols_same_col);

    suite_add_tcase(s, tc_pos);

    return s;
}

// Строка матрицы - нулевая
START_TEST(test_check_zero_line_true)
{
    double line[] = {0, 0, 0, 0, 0};
    int cr = check_zero_line(line, 5);

    ck_assert_int_eq(cr, 1);
}
END_TEST

// Строка матрицы - ненулевая
START_TEST(test_check_zero_line_false)
{
    double line[] = {0, 0, 0, 1, 0};
    int cr = check_zero_line(line, 5);

    ck_assert_int_eq(cr, 0);
}
END_TEST

Suite* check_zero_line_suite(Suite *s)
{
    TCase *tc_pos;

    tc_pos = tcase_create("positives");
    tcase_add_test(tc_pos, test_check_zero_line_true);
    tcase_add_test(tc_pos, test_check_zero_line_false);

    suite_add_tcase(s, tc_pos);

    return s;
}

// Решение слау: некорректные размеры
START_TEST(test_gauss_solving_bad_sizes)
{
    size_t n = 3, m = 2;

    double data[3][2] = {{1, 2}, {3, 4}, {5, 6}};
    double* data_pointers[3] = {data[0], data[1], data[2]};

    double **res_col;

    int cr = gauss_solving(data_pointers, n, m, &res_col);
    ck_assert_int_eq(cr, MATRIX_SIZE_ERROR);
}
END_TEST

// Решение слау: бесконечное множество решений
START_TEST(test_gauss_solving_inf_solutions)
{
    size_t n = 2, m = 3;

    double data[2][3] = {{1, 2, 3}, {2, 4, 6}};
    double* data_pointers[2] = {data[0], data[1]};

    double **res_col;

    int cr = gauss_solving(data_pointers, n, m, &res_col);
    ck_assert_int_eq(cr, INF_SOLUTIONS);
}
END_TEST

// Решение слау: нет решений
START_TEST(test_gauss_solving_zero_solutions)
{
    size_t n = 2, m = 3;

    double data[2][3] = {{1, 2, 3}, {2, 4, 3}};
    double* data_pointers[2] = {data[0], data[1]};

    double **res_col;

    int cr = gauss_solving(data_pointers, n, m, &res_col);
    ck_assert_int_eq(cr, ZERO_SOLUTIONS);
}
END_TEST

// Решение слау: обычный тест
START_TEST(test_gauss_solving_simple)
{
    size_t n = 4, m = 5;

    double data[4][5] = {{1, 4, 8, -2, 12}, {34, -17, 18, 10, 15}, {-12, -6, 3, -7, 1}, {5, 11, 43, -2, 3}};
    double* data_pointers[4] = {data[0], data[1], data[2], data[3]};

    double **res_col;
    double res_col_expect[4][1] = {{ 2.955746 }, { 0.670633} , { -0.729069 }, { -6.097137 }};
    double *res_col_pointers[4] = {res_col_expect[0], res_col_expect[1], res_col_expect[2], res_col_expect[3]};

    int cr = gauss_solving(data_pointers, n, m, &res_col);
    ck_assert_int_eq(cr, OK);

    check_values(res_col, res_col_pointers, n, 1);

    matrix_free(res_col, n);
}
END_TEST

// Решение слау: одна неизвестная
START_TEST(test_gauss_solving_one_row)
{
    size_t n = 1, m = 2;

    double data[1][2] = {{-3, 12}};
    double* data_pointers[1] = { data[0] };

    double **res_col;
    double res_col_expect[1][1] = {{ -4 }};
    double *res_col_pointers[1] = { res_col_expect[0] };

    int cr = gauss_solving(data_pointers, n, m, &res_col);
    ck_assert_int_eq(cr, OK);

    check_values(res_col, res_col_pointers, n, 1);

    matrix_free(res_col, n);
}
END_TEST

Suite* gauss_solving_suite(Suite *s)
{
    TCase *tc_neg, *tc_pos;

    tc_neg = tcase_create("negatives");
    tcase_add_test(tc_neg, test_gauss_solving_bad_sizes);
    tcase_add_test(tc_neg, test_gauss_solving_inf_solutions);
    tcase_add_test(tc_neg, test_gauss_solving_zero_solutions);

    suite_add_tcase(s, tc_neg);

    tc_pos = tcase_create("positives");
    tcase_add_test(tc_pos, test_gauss_solving_simple);
    tcase_add_test(tc_pos, test_gauss_solving_one_row);

    suite_add_tcase(s, tc_pos);

    return s;
}
