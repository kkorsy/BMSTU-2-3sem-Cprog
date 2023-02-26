#include <stdio.h>
#include <math.h>
#define OK 0
#define ERROR 1
#define N 10

int input_array(int *a, int n);
int is_square(int x);
void del_element(int *a, int n, int index);
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
            int i = 0;
            while (i < len_array)
            {
                if (is_square(a[i]))
                {
                    del_element(a, len_array, i);
                    len_array -= 1;
                }
                else
                    i += 1;
            }

            if (len_array == 0)
                code_error = ERROR;
            else
                array_print(a, len_array);
        }
    }

    return code_error;
}

void array_print(int *a, int n)
{
    for (int i = 0; i < n; i++)
        printf("%d ", a[i]);
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

int is_square(int x)
{
    int res = 0;
    if (sqrt(x) - (int) sqrt(x) == 0)
        res = 1;

    return res;
}

void del_element(int *a, int n, int index)
{
    for (int i = index; i < n; i++)
        a[i] = a[i + 1];
}
