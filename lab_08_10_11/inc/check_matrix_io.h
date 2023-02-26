#ifndef __CHECK_MATRIX_IO_H__
#define __CHECK_MATRIX_IO_H__

#include <check.h>

void check_values(double **data, double **data_expect, size_t n, size_t m);
Suite* matrix_create_suite(Suite *s);
Suite* matrix_read_suite(Suite *s);

#endif
