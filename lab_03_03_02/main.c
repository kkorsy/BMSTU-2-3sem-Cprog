#include <stdio.h>
#define OK 0
#define ERROR 1
#define N 10

void transform(int **p, int *buf, int n, int m);
int matrix_input(int **a, int n, int m);
void matrix_print(int **a, int n, int m);
void matrix_sort(int **a, int n, int m);
void swap_rows(int **a, int i);
int row_product(int **a, int m, int i);

int main(void)
{
    int a[N][N] = { { 0 } }, code_return = OK;
    int n, m, *p[N];

    if (scanf("%d %d", &n, &m) != 2 || n > 10 || m > 10 || n < 1 || m < 1)
        code_return = ERROR;
    else
    {
        transform(p, (int *) a, n, m);
        code_return = matrix_input(p, n, m);

        if (code_return != ERROR)
        {
            matrix_sort(p, n, m);
            matrix_print(p, n, m);
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

void matrix_sort(int **a, int n, int m)
{
    for (int i = 1; i < n; i++)
        for (int j = i; j > 0 && row_product(a, m, j - 1) > row_product(a, m, j); j--)
            swap_rows(a, j);
}

int row_product(int **a, int m, int i)
{
    int res = 1;
    for (int j = 0; j < m; j++)
        res *= *(a[i] + j);

    return res;
}

void swap_rows(int **a, int i)
{
    int *temp = a[i];
    a[i] = a[i - 1];
    a[i - 1] = temp;
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
