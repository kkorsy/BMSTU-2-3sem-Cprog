#include <stdio.h>
#include "sort.h"

// void mysort(void *base, size_t n, size_t elem_size, int (*cmp)(const void *, const void *))
// {
//     char *pbeg = base;
//     char *pend = pbeg + elem_size * n;

//     for (char *p1 = pbeg + elem_size; p1 < pend; p1 += elem_size)
//         for (char *p2 = p1; p2 > pbeg && cmp(p2 - elem_size, p2) > 0; p2 -= elem_size)
//             swap(p2 - elem_size, p2, elem_size);
// }

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
