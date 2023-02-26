#include <stdio.h>
#include "arr_lib.h"

#define OK 0
#define SMALL_SIZE 1

void fill_fib(long long unsigned *arr, int n)
{
    long long unsigned cur = 0, next = 1;
    long long unsigned temp;

    for (int i = 0; i < n; i++)
    {
        arr[i] = cur;

        temp = next;
        next += cur;
        cur = temp;
    }
}

bool is_in_arr(int *arr, int n, int x)
{
    for (int i = 0; i < n; i++)
        if (arr[i] == x)
            return true;
    return false;
}

int rm_duplicates(int *src, int src_len, int *dst, int *dst_len)
{
    int n = 0;
    for (int i = 0; i < src_len; i++)
        if (!is_in_arr(src, i, src[i]))
            n++;

    if (n > *dst_len)
    {
        *dst_len = n;
        return SMALL_SIZE;
    }
    
    n = 0;
    for (int i = 0; i < src_len; i++)
        if (!is_in_arr(src, i, src[i]))
            dst[n++] = src[i];

    *dst_len = n;

    return OK;            
}
