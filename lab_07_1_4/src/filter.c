#include "filter.h"

int key(const int *pb_src, const int *pe_src, int **pb_dst, int **pe_dst)
{
    if (pb_src == NULL || pe_src == NULL || pb_src >= pe_src)
        return PARAM_ERROR;

    double avg = average(pb_src, pe_src);
    
    int n = num_count(pb_src, pe_src, avg);
    if (n == 0)
        return DATA_ERROR;

    *pb_dst = malloc(n * sizeof(int));
    if (*pb_dst == NULL)
        return ALLOC_ERROR;

    *pe_dst = *pb_dst + n;
    copy(pb_src, pe_src, *pb_dst, avg);

    return OK;
}

void copy(const int *pb_src, const int *pe_src, int *const pb_dst, double avg)
{
    int *pi = pb_dst;
    const int *pcur = pb_src;

    while (pcur != pe_src)
    {
        if (*pcur > avg)
            *pi++ = *pcur;
        pcur++;
    }
}

int num_count(const int *pb, const int *pe, double avg)
{
    int count = 0;

    for (const int *pcur = pb; pcur != pe; pcur++)
        if (*pcur > avg)
            count++;

    return count;
}

double average(const int *pb, const int *pe)
{
    int sum = 0, k = 0;

    for (const int *pcur = pb; pcur != pe; pcur++)
    {
        sum += *pcur;
        k++;
    }

    return (double) sum / k;
}
