#include <math.h>
#include "find_num.h"

int find_num(FILE *f, double *res, double avg)
{
    int code_return = OK;
    double num, eps;

    fscanf(f, "%lf", &num);
    eps = fabs(num - avg);
    *res = num;

    while (fscanf(f, "%lf", &num) == 1)
        if (fabs(num - avg) < eps)
        {
            eps = fabs(num - avg);
            *res = num;
        }
    
    return code_return;
}

int average(FILE *f, double *avg)
{
    int code_return = OK;
    double x, sum = 0;
    int k = 0;

    if (fscanf(f, "%lf", &x) != 1)
        code_return = NO_DATA;
    else
    {
        sum += x;
        k++;

        while (fscanf(f, "%lf", &x) == 1)
        {
            sum += x;
            k++;
        }
        *avg = sum / k;
    }

    return code_return;
}