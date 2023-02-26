#include "check_matrix_io.h"
#include "matrix_io.h"
#include "matrix_alloc.h"
#include <stdlib.h>

#define EPS 1e-06

void check_values(double **data, double **data_expect, size_t n, size_t m)
{
    for (size_t i = 0; i < n; i++)
        for (size_t j = 0; j < m; j++)
            ck_assert_double_eq_tol(data[i][j], data_expect[i][j], EPS);
}

// Некорректное имя файла для считывания матрицы
START_TEST(test_create_bad_filename)
{
    size_t n, m;
    int cr = matrix_create("abc.txt", NULL, &n, &m);

    ck_assert_int_eq(cr, OPEN_ERROR);
}
END_TEST

// Некорректные размеры матрицы
START_TEST(test_create_bad_sizes)
{
    double **data;
    size_t n, m;
    int cr = matrix_create("./func_tests/data/neg_07.txt", &data, &n, &m);
    ck_assert_int_eq(cr, READ_ERROR);
}
END_TEST

// Некорректные символы в матрице
START_TEST(test_create_bad_matrix)
{
    double **data;
    size_t n, m;
    int cr = matrix_create("./func_tests/data/neg_08.txt", &data, &n, &m);

    ck_assert_int_eq(cr, READ_ERROR);
}
END_TEST

// Данных в файле больше, чем указано
START_TEST(test_create_more_data)
{
    double **data;
    size_t n, m;
    int cr = matrix_create("./func_tests/data/neg_24.txt", &data, &n, &m);

    ck_assert_int_eq(cr, MORE_DATA_ERROR);
}
END_TEST

// Считывание корректной матрицы
START_TEST(test_create_correct)
{
    double **data;
    size_t n, m;
    int cr = matrix_create("./func_tests/data/file_2_a.txt", &data, &n, &m);
    ck_assert_int_eq(cr, OK);

    double d[2][3] = {{ 4, 3, 2 }, { 7, 6, 5 }};
    double *data_expect[2] = { d[0], d[1] };

    check_values(data, data_expect, n, m);

    matrix_free(data, n);
}
END_TEST

// Считывание матрицы 1 х 1
START_TEST(test_create_one_elem)
{
    double **data;
    size_t n, m;
    int cr = matrix_create("./func_tests/data/file_4_a.txt", &data, &n, &m);
    ck_assert_int_eq(cr, OK);

    double d[1][1] = {{ 5 }};
    double *data_expect[1] = { d[0] };

    check_values(data, data_expect, n, m);

    matrix_free(data, n);
}
END_TEST

Suite* matrix_create_suite(Suite *s)
{
    TCase *tc_neg, *tc_pos;

    tc_neg = tcase_create("negatives");
    tcase_add_test(tc_neg, test_create_bad_filename);
    tcase_add_test(tc_neg, test_create_bad_sizes);
    tcase_add_test(tc_neg, test_create_bad_matrix);
    tcase_add_test(tc_neg, test_create_more_data);

    suite_add_tcase(s, tc_neg);

    tc_pos = tcase_create("positives");
    tcase_add_test(tc_pos, test_create_correct);
    tcase_add_test(tc_pos, test_create_one_elem);

    suite_add_tcase(s, tc_pos);

    return s;
}

// Некорректные символы в матрице
START_TEST(test_read_bad_matrix)
{
    FILE *f = fopen("./func_tests/data/neg_08.txt", "r");
    double d[2][2];
    double *data[2] = {d[0], d[1]};
    size_t n = 2, m = 2;
    int cr = matrix_read(f, data, n, m);

    ck_assert_int_eq(cr, READ_ERROR);
}
END_TEST

// Считывание корректной матрицы
START_TEST(test_read_correct)
{
    FILE *f = fopen("./func_tests/data/file_2_a.txt", "r");
    double d[2][3];
    double *data[2] = {d[0], d[1]};

    size_t n, m;
    fscanf(f, "%zu%zu\n", &n, &m);
    
    int cr = matrix_read(f, data, n, m);
    ck_assert_int_eq(cr, OK);

    double dexp[2][3] = {{4, 3, 2}, {7, 6, 5}};
    double *data_expect[2] = {dexp[0], dexp[1]};

    check_values(data, data_expect, n, m);
}
END_TEST

// Считывание матрицы 1 х 1
START_TEST(test_read_one_elem)
{
    FILE *f = fopen("./func_tests/data/file_4_a.txt", "r");
    double d[1][1];
    double *data[1] = { d[0] };

    size_t n, m;
    fscanf(f, "%zu%zu\n", &n, &m);

    int cr = matrix_read(f, data, n, m);
    ck_assert_int_eq(cr, OK);

    double dexp[1][1] = {{ 5 }};
    double *data_expect[1] = { dexp[0] };

    check_values(data, data_expect, n, m);
}
END_TEST

Suite* matrix_read_suite(Suite *s)
{
    TCase *tc_neg, *tc_pos;

    tc_neg = tcase_create("negatives");
    tcase_add_test(tc_neg, test_read_bad_matrix);

    suite_add_tcase(s, tc_neg);

    tc_pos = tcase_create("positives");
    tcase_add_test(tc_pos, test_read_correct);
    tcase_add_test(tc_pos, test_read_one_elem);

    suite_add_tcase(s, tc_pos);

    return s;
}
