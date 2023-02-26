#include <stdio.h>
int hours(int t);
int min(int t, int h);
int sec(int t, int h, int m);

int main(void)
{
    int t, h, m, s;
    scanf("%d", &t);
    h = hours(t);
    m = min(t, h);
    s = sec(t, h, m);
    printf("%d %d %d", h, m, s);

    return 0;
}

int hours(int t)
{
    return t / 3600;
}

int min(int t, int h)
{
    return (t - (h * 3600)) / 60;
}

int sec(int t, int h, int m)
{
    return t - h * 3600 - m * 60;
}
