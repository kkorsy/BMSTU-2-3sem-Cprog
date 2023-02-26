#ifndef __ARR_LIB_H__
#define __ARR_LIB_H__

#include <stdbool.h>

void fill_fib(long long unsigned *arr, int n);
int rm_duplicates(int *src, int src_len, int *dst, int *dst_len);

bool is_in_arr(int *arr, int n, int x);

#endif
