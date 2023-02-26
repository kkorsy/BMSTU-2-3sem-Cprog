#include <stdio.h>
#include <math.h>
#define OK 0
#define ERROR 1

double func(double x);
double s(double x, double n);
double sum_row(double x, double e);

int main(void)
{
    double x, e;
    int code_error, k;

    k = scanf("%lf %lf", &x, &e);
    if (k != 2 || x <= -1 || x >= 1 || e <= 0 || e > 1)
        code_error = ERROR;
    else
    {
        code_error = OK;
        double f = func(x);
        double absolut, sum;

        sum = sum_row(x, e);
        absolut = fabs(f - sum);

        printf("%lf %lf %lf %lf", sum, f, absolut, absolut / fabs(f));
    }

    return code_error;
}

double sum_row(double x, double e)
{
    double f = func(x);
    int n = 2;
    double s_n = s(x, n), sum = 1 + s_n;

    while (fabs(f - sum) >= e)
    {
        n = n + 1;
        s_n = s(x, n);
        sum = sum + s_n;
    }

    return sum;
}

//s(x) = 1 - (2*3*x)/2 + (3*4*x^2)/2 - (4*5*x^3)/2 + ...
double s(double x, double n)
{
    double t;
    t = ((n * (n + 1) * pow(x, n - 1)) / 2) * pow(-1, n + 1);

    return t;
}

//f(x) = 1 / (1+x)^3
double func(double x)
{
    double t;
    t = 1 / (pow(1 + x, 3));

    return t;
}
