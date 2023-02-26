#include <stdio.h>
#define OK 0
#define ERROR 1
#define N 10

int matrix_input(int **a, int n, int m);
void array_fill(int **a, int *res, int n, int m);
void array_print(int *res, int m);
void transform(int **p, int *buf, int n, int m);

int main(void)
{
    int a[N][N] = { { 0 } }, code_return = OK;
    int n, m, *p[N];

    if (scanf("%d %d", &n, &m) != 2 || n > N || m > N || n < 1 || m < 1)
        code_return = ERROR;
    else
    {
        transform(p, (int *) a, n, m);
        code_return = matrix_input(p, n, m);

        if (code_return != ERROR)
        {
            int res[N] = { 0 };
            if (n > 1)
                array_fill(p, res, n, m);
            array_print(res, m);
        }
    }

    return code_return;
}

void transform(int **p, int *buf, int n, int m)
{
    for (int i = 0; i < n; i++)
        p[i] = buf + i * m;
}

int matrix_input(int **a, int n, int m)
{
    int element, code_return = OK;

    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
        {
            if (scanf("%d", &element) != 1 || code_return == ERROR)
                code_return = ERROR;
            else
                *(a[i] + j) = element;
        }

    return code_return;
}

void array_fill(int **a, int *res, int n, int m)
{
    for (int k = 0; k < m; k++)
    {
        int flag = 0;
        for (int i = 0; i < n - 1; i++)
        {
            if (*(*(a + i) + k) * *(*(a + i + 1) + k) >= 0)
                flag = 1;
        }

        if (flag)
            res[k] = 0;
        else
            res[k] = 1;
    }
}

void array_print(int *res, int n)
{
    for (int i = 0; i < n; i++)
        printf("%d ", res[i]);
}
