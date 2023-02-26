#include <stdio.h>
int is_on_line(int x1, int y1, int x2, int y2, int x, int y);

int main(void)
{
    int xq, yq, xr, yr;
    int xp, yp;
    int k, code_error, i;

    k = scanf("%d %d %d %d %d %d", &xq, &yq, &xr, &yr, &xp, &yp);
    if (k != 6 || (xq == xr && yq == yr))
        code_error = 1;
    else
    {
        code_error = 0;
        i = is_on_line(xq, yq, xr, yr, xp, yp);

        printf("%d", i);
    }

    return code_error;
}

int is_on_line(int x1, int y1, int x2, int y2, int x, int y)
{
    int k, scalar;
    scalar = (x - x1) * (y2 - y1) - (y - y1) * (x2 - x1);

    if (scalar == 0 && ((x1 <= x && x <= x2) || (x2 <= x && x <= x1)))
        k = 1;
    else
        k = 0;

    return k;
}
