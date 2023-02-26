#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "sort.h"

#define N 25000

unsigned long long int get_time(void);
void create_array(int *a, size_t n);

int main(void)
{
    unsigned long long int beg, end;
    int a[N];
    FILE *f = fopen("mysort.txt", "w");
    
    for (size_t i = 2; i < N; i += 500)
    {
        create_array(a, i);

        beg = get_time();
        mysort(a, i, sizeof(int), cmp);
        end = get_time();

        fprintf(f, "%zu %lld\n", i, (end - beg));
    }
    fclose(f);

    return 0;
}

unsigned long long int get_time(void)
{
    struct timespec ts;
    clock_gettime(CLOCK_MONOTONIC, &ts);

    return ts.tv_sec * 1000000000 + ts.tv_nsec;
}

void create_array(int *a, size_t n)
{
    for (size_t i = 0; i < n; i++)
        a[i] = i % 10;
}
