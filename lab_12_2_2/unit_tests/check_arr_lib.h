#ifndef __CHECK_ARR_LIB_H__
#define __CHECK_ARR_LIB_H__

#include <check.h>

void check_arr(long long unsigned *exp_arr, long long unsigned *arr, int n);
void check_arr_int(int *exp_arr, int *arr, int n);
Suite* fill_fib_suite(Suite *s);
Suite* is_in_arr_suite(Suite *s);
Suite* rm_dupl_suite(Suite *s);

#endif