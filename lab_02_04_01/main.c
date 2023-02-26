#include <stdio.h>
#define OK 0
#define ERROR 1
#define OVERFLOW 100
#define N 10

void sort(int *a, int n);
int input_array(int *a);
void array_print(int *a, int n);
void swap(int *a, int *b);

int main(void)
{
    int a[N] = { 0 }, code_error = OK;

    int n = input_array(a);

    if (n == 0)
        code_error = ERROR;
    else
    {
        if (n == N + 1)
        {
            code_error = OVERFLOW;
            n = N;
        }
        sort(a, n);

        array_print(a, n);
    }

    return code_error;
}

void array_print(int *a, int n)
{
    for (int i = 0; i < n; i++)
        printf("%d ", a[i]);
}

int input_array(int *a)
{
    int element, k = 1, n = 0;
    while (k == 1 && n < N + 1)
    {
        k = scanf("%d", &element);
        if (k == 1)
        {
            if (n < N)
                a[n] = element;
            n += 1;
        }
    }

    return n;
}

void sort(int *a, int n)
{
    for (int i = 1; i < n; i++)
        for (int j = i; j > 0 && a[j - 1] > a[j]; j--)
        {
            swap(a + j, a + j - 1);
        }
}

void swap(int *a, int *b)
{
    int temp;
    temp = *a;
    *a = *b;
    *b = temp;
}
