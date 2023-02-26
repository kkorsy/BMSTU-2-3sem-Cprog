#include <stdio.h>
#define ERROR 1
#define OK 0
#define N 10

int input_array(int *a, int n);
float average(int *a, int n);

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
            float avr_res = average(a, len_array);

            if (avr_res == 0)
                code_error = ERROR;
            else
                printf("%f\n", avr_res);
        }
    }

    return code_error;
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

float average(int *a, int n)
{
    int sum = 0, k = 0;
    float res = 0;
    for (int i = 0; i < n; i++)
    {
        if (a[i] < 0)
        {
            sum += a[i];
            k += 1;
        }
    }

    if (k != 0)
        res = (float) sum / k;

    return res;
}
