#include <stdio.h>
#include <stdlib.h>
#define OK 0
#define ERROR 1
#define N 10

void transform(int **p, int *buf, int n, int m);
int matrix_input(int **a, int n, int m);
void matrix_print(int **a, int n, int m);
void insert_strings(int **a, int *n, int m, int *);
void insertion(int **a, int *line, int n, int i);
int sum_digits(int x);
void line_fill(int *line, int m);

int main(void)
{
    int a[N][N] = { { 0 } }, code_return = OK;
    int n, m, *p[N], line[N];

    if (scanf("%d %d", &n, &m) != 2 || n > 10 || m > 10 || n < 1 || m < 1)
        code_return = ERROR;
    else
    {
        transform(p, (int *) a, n, m);
        code_return = matrix_input(p, n, m);

        if (code_return != ERROR)
        {
            line_fill(line, m);
            insert_strings(p, &n, m, line);
            matrix_print(p, n, m);
        }
    }

    return code_return;
}

void line_fill(int *line, int m)
{
    for (int j = 0; j < m; j++)
        line[j] = -1;
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

void insert_strings(int **a, int *n, int m, int *line)
{
    int i = 0;
    while (i < *n)
    {
        int counter = 0;
        for (int j = 0; j < m; j++)
        {
            if (sum_digits(*(a[i] + j)) % 2 != 0)
                counter++;
        }

        if (counter >= 2)
        {
            insertion(a, line, *n, i);
            (*n)++;
            i += 2;
        }
        else
            i++;
    }
}

void insertion(int **a, int *line, int n, int i)
{
    for (int k = n; k > i; k--)
        a[k] = a[k - 1];

    a[i] = line;
}

int sum_digits(int x)
{
    int sum = 0;
    if (x < 0)
        x = abs(x);

    while (x > 0)
    {
        sum += x % 10;
        x /= 10;
    }

    return sum;
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
