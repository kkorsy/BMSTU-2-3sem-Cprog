//2 вариант

#include <stdio.h>
#define N 10
#define OK 0
#define ERROR 1

int input(int a[]);
void group(int a[], int n);
void output(int a[], int n);

int main(void)
{
    int a[N], len, code_error = OK;

    len = input(a);

    if (len == -1)
        code_error = ERROR;
    else
        group(a, len);

    return code_error;
}

int input(int a[])
{
    int len;
    if (scanf("%d", &len) != 1 || len <= 0 || len > N)
        return -1;
    else
        for (int i = 0; i < len; i++)
        {
            int element;
            if (scanf("%d", &element) != 1)
                return -1;
            else
                a[i] = element;
        }

    return len;
}

void output(int a[], int n)
{
    for (int i = 0; i < n; i++)
        printf("%d ", a[i]);
}

void group(int a[], int n)
{
    int a_group[N], j = 0;
    for (int i = 0; i < n; i++)
    {
        if (a[i] % 2 == 0 && a[i] != 0)
        {
            a_group[j] = a[i];
            j += 1;
        }
    }

    for (int i = 0; i < n; i++)
    {
        if (a[i] % 2 != 0)
        {
            a_group[j] = a[i];
            j += 1;
        }
    }

    for (int i = 0; i < n; i++)
    {
        if (a[i] == 0)
        {
            a_group[j] = a[i];
            j += 1;
        }
    }

    output(a_group, n);
}
