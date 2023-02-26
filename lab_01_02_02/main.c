#include <stdio.h>
#include <math.h>
double len(float a, float b);

double perimetr(float x1, float x2, float x3, float y1, float y2, float y3);

int main(void)
{
    float xa, xb, xc;
    float ya, yb, yc;

    scanf("%f %f %f %f %f %f", &xa, &ya, &xb, &yb, &xc, &yc);

    printf("%lf\n", perimetr(xa, xb, xc, ya, yb, yc));

    return 0;
}

double len(float a, float b)
{
    double l;
    l = sqrt(a * a + b * b);

    return l;
}

double perimetr(float x1, float x2, float x3, float y1, float y2, float y3)
{
    double p;
    p = len(x1 - x2, y1 - y2) + len(x2 - x3, y2 - y3) + len(x1 - x3, y1 - y3);

    return p;
}
