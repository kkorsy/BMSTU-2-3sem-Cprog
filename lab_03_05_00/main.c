#include <stdio.h>
#include <math.h>
#define OK 0
#define ERROR 1
#define N 10

void transform(int **p, int *buf, int n, int m);
int matrix_input(int **a, int n, int m);
void matrix_print(int **a, int n, int m);
int matrix_traversing(int **a, int n, int m);
void array_reversing(int *r, int k);
void return_elements(int **a, int *r, int n, int m);
int is_prime(int x);

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
            code_return = matrix_traversing(p, n, m);
            if (code_return != ERROR)
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

int matrix_traversing(int **a, int n, int m)
{
    int code_return = OK;
    int r[N * N] = { 0 }, k = -1;

    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            if (is_prime(*(a[i] + j)))
            {
                k += 1;
                r[k] = *(a[i] + j);
            }

    if (k == -1)
        code_return = ERROR;
    else
    {
        array_reversing(r, k);
        return_elements(a, r, n, m);
    }

    return code_return;
}

void return_elements(int **a, int *r, int n, int m)
{
    int k = 0;
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            if (is_prime(*(a[i] + j)))
            {
                *(a[i] + j) = r[k];
                k++;
            }
}

void array_reversing(int *r, int k)
{
    for (int i = 0; i <= k / 2; i++)
    {
        int temp = r[i];
        r[i] = r[k - i];
        r[k - i] = temp;
    }
}

int is_prime(int x)
{
    int res = 1;
    if (x <= 1)
        res = 0;

    for (int i = 2; res && i <= sqrt(x); i++)
        if (x % i == 0)
            res = 0;

    return res;
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
