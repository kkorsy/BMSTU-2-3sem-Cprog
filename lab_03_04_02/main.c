#include <stdio.h>
#include <stdlib.h>
#define OK 0
#define ERROR 1
#define N 10

void transform(int **p, int *buf, int n, int m);
int matrix_input(int **a, int n, int m);
int find_element(int **a, int n, int m);

int main(void)
{
    int a[N][N] = { { 0 } }, code_return = OK;
    int n, m, *p[N];

    if (scanf("%d %d", &n, &m) != 2 || n != m || n > 10 || n < 2)
        code_return = ERROR;
    else
    {
        transform(p, (int *) a, n, m);
        code_return = matrix_input(p, n, m);

        if (code_return != ERROR)
        {
            int res = find_element(p, n, m);
            if (res != -1)
                printf("%d", res);
            else
                code_return = ERROR;
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

int find_element(int **a, int n, int m)
{
    int res = -1;
    for (int i = 1; i < n; i++)
        for (int j = m - i; j < m; j++)
        {
            if (abs(*(a[i] + j)) % 10 == 5 && (*(a[i] + j) > res || res == -1))
                res = *(a[i] + j);
        }

    return res;
}
