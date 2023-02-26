#include <stdio.h>
#define N 10
#define ERROR 1
#define OK 0

int max(int *pbeg, int *pend);
int input_array(int *a, int n);

int main(void)
{
    int a[N] = { 0 }, len_array, code_error = OK;
    if (scanf("%d", &len_array) != 1 || len_array > N || len_array <= 0)
        code_error = ERROR;
    else
    {
        code_error = input_array(a, len_array);
        if (code_error == OK)
            printf("%d", max(a, a + len_array));
    }

    return code_error;
}

int input_array(int *a, int n)
{
    int code_error = OK;
    for (int i = 0; i < n; i++)
    {
        int element, *pa = a;
        if (scanf("%d", &element) != 1)
            code_error = ERROR;
        else
            *(pa + i) = element;
    }
    return code_error;
}

int max(int *pbeg, int *pend)
{
    int *pb_cur = pbeg, *pe_cur = pend - 1;
    int maxi = *pbeg + *(pend - 1);

    while (pb_cur <= pe_cur)
    {
        int sum = *pb_cur + *pe_cur;

        if (sum > maxi)
            maxi = sum;
        pb_cur += 1;
        pe_cur -= 1;
    }

    return maxi;
}
