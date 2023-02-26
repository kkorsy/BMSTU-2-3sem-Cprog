#ifndef __CHECK_MATRIX_OP_H__
#define __CHECK_MATRIX_OP_H__

#include <check.h>

void check_values(double **data, double **data_expect, size_t n, size_t m);
Suite* matrix_mult_suite(Suite *s);
Suite* matrix_sum_suite(Suite *s);
Suite* find_max_suite(Suite *s);
Suite* swap_cols_suite(Suite *s);
Suite* check_zero_line_suite(Suite *s);
Suite* gauss_solving_suite(Suite *s);

#endif