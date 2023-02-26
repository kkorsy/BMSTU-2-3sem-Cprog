#include <stdio.h>
#define OK 0
#define ERROR 1
#define N 10

void transform(int **p, int *buf, int n, int m);
void matrix_fill(int **a, int n, int m);
void matrix_print(int **a, int n, int m);
int fill_up(int **a, int n, int j, int k);
int fill_down(int **a, int n, int j, int k);

int main(void)
{
    int a[N][N] = { { 0 } }, code_return = OK;
    int n, m, *p[N];

    if (scanf("%d %d", &n, &m) != 2 || n > 10 || m > 10 || n < 1 || m < 1)
        code_return = ERROR;
    else
    {
        transform(p, (int *) a, n, m);
        matrix_fill(p, n, m);
        matrix_print(p, n, m);
    }

    return code_return;
}

void transform(int **p, int *buf, int n, int m)
{
    for (int i = 0; i < n; i++)
        p[i] = buf + i * m;
}

void matrix_fill(int **a, int n, int m)
{
    int k = 1, flag = 1;
    for (int t = m - 1; t >= 0; t--)
    {
        if (flag)
        {
            k = fill_up(a, n, t, k);
            flag = 0;
        }
        else
        {
            k = fill_down(a, n, t, k);
            flag = 1;
        }
    }
}

int fill_up(int **a, int n, int j, int k)
{
    for (int i = n - 1; i >= 0; i--)
    {
        *(a[i] + j) = k;
        k++;
    }

    return k;
}

int fill_down(int **a, int n, int j, int k)
{
    for (int i = 0; i < n; i++)
    {
        *(a[i] + j) = k;
        k++;
    }

    return k;
}

void matrix_print(int **a, int n, int m)
{
    for (int i = 0; i < n; i++)
    {
        printf("\n");
        for (int j = 0; j < m; j++)
            printf("%d ", *(a[i] + j));
    }
}
