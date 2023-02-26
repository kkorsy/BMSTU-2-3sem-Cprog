#include <stdio.h>
#include <stdlib.h>
#define OK 0
#define ERROR 1
#define N 10

int input_array(int *a, int n);
int check_numbs(int x);
int form_checked_array(int *checked_a, int *a, int n);
void array_print(int *a, int n);

int main(void)
{
    int len_array, code_error = OK;
    if (scanf("%d", &len_array) != 1 || len_array > N || len_array <= 0)
        code_error = ERROR;
    else
    {
        int a[N] = { 0 };

        code_error = input_array(a, len_array);

        if (code_error == OK)
        {
            int checked_a[N], count = form_checked_array(checked_a, a, len_array);

            if (count == 0)
                code_error = ERROR;
            else
                array_print(checked_a, count);
        }
    }

    return code_error;
}

void array_print(int *a, int n)
{
    for (int i = 0; i < n; i++)
        printf("%d ", a[i]);
}

int form_checked_array(int *checked_a, int *a, int n)
{
    int j = 0;
    for (int i = 0; i < n; i++)
    {
        if (check_numbs(a[i]))
        {
            checked_a[j] = a[i];
            j += 1;
        }
    }

    return j;
}

int input_array(int *a, int n)
{
    int code_error = OK;
    for (int i = 0; i < n; i++)
    {
        int element;
        if (scanf("%d", &element) != 1)
            code_error = ERROR;
        else
            a[i] = element;
    }
    return code_error;
}

int check_numbs(int x)
{
    int result;
    if (x == 0)
        result = 1;
    else
    {
        if (x < 0)
            x = abs(x);

        int x_saved = x, first;
        while (x > 0)
        {
            first = x % 10;
            x /= 10;
        }

        if (x_saved % 10 == first)
            result = 1;
        else
            result = 0;
    }

    return result;
}
