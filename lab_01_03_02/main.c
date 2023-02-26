#include <stdio.h>
double resistance(double r1, double r2, double r3);

int main(void)
{
    double r1, r2, r3;

    scanf("%lf%lf%lf", &r1, &r2, &r3);

    printf("%lf\n", resistance(r1, r2, r3));

    return 0;
}

double resistance(double r1, double r2, double r3)
{
    return (r1 * r2 * r3) / (r1 * r2 + r2 * r3 + r3 * r1);
}
