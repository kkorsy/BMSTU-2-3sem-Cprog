#include "lib_arr.h"
#include <stdlib.h>

void mysort(void *base, size_t n, size_t elem_size, int (*cmp)(const void *, const void *))
{
    char *pbeg = base;
    char *pend = pbeg + elem_size * n;
    char *max;

    for (char *p1 = pend - elem_size; p1 > pbeg; p1 -= elem_size)
    {
        max = p1;
        for (char *p2 = pbeg; p2 < p1; p2 += elem_size)
            if (cmp(p2, max) > 0)
                max = p2;
        swap(p1, max, elem_size);
    }
}

int cmp(const void *pl, const void *pr)
{
    return *(int *)pl - *(int *)pr;
}

void swap(void *pl, void *pr, size_t elem_size)
{
    char *p1 = pl, *p2 = pr, temp;

    for (size_t i = 0; i < elem_size; i++)
    {
        temp = *p1;
        *p1 = *p2;
        *p2 = temp;

        p1++;
        p2++;
    }
}

void key(const int *pb_src, const int *pe_src, int *const pb_dst, double avg)
{
    int *pi = pb_dst;
    const int *pcur = pb_src;

    while (pcur != pe_src)
    {
        if (*pcur > avg)
        {
            *pi = *pcur;
            pi++;
        }
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

int array_write(char *file_name, int *pb, int *pe)
{
    int cr = OK;
    FILE *f = fopen(file_name, "w");

    if (!f)
        return OPEN_ERROR;

    cr = print(f, pb, pe);
    fclose(f);
    
    return cr;
}

int print(FILE *f, int *pb, int *pe)
{
    int cr = OK;
    for (int *p = pb; p < pe && !cr; p++)
        if (fprintf(f, "%d ", *p) < 0)
            cr = WRITE_ERROR;
    
    return cr;
}

int array_read(char *file_name, int **arr, size_t *n)
{
    int cr = OK;
    FILE *f = fopen(file_name, "r");
    if (!f)
        return OPEN_ERROR;
    
    cr = elem_count(f, n);
    if (cr == OK)
    {
        *arr = malloc(*n * sizeof(int));
        if (*arr == NULL)
            cr = ALLOC_ERROR;
        else
        {
            rewind(f);
            array_fill(f, *arr, *arr + *n);
        }
    }
    fclose(f);

    return cr;
}

void array_fill(FILE *f, int *pb, int *pe)
{
    for (int *p = pb; p < pe; p++)
        fscanf(f, "%d", p);
}

int elem_count(FILE *f, size_t *n)
{
    int count = 0, temp, cr = OK;

    while (fscanf(f, "%d", &temp) == 1)
        count++;
    
    if (count != 0)
        *n = count;
    else
        cr = DATA_ERROR;
    
    return cr;
}

