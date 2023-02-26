#include <stdio.h>
#include <math.h>
#define OK 0
#define ERROR 1
double g(double x, int n);

int main(void)
{
    int code_error = OK, n = 0, k;
    double x, sum = 0;

    k = scanf("%lf", &x);
    while (k == 1 && x >= 0)
    {
        n += 1;
        sum += g(x, n);
        k = scanf("%lf", &x);
    }

    if (k != 1 || n == 0)
        code_error = ERROR;
    else
    {
        code_error = OK;
        sum *= (1.0 / n);
        printf("%lf", sum);
    }

    return code_error;
}

double g(double x, int n)
{
    return sqrt(n + x);
}
