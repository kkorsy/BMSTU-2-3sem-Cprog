#include <stdio.h>
void prime(int n);

int main(void)
{
    int n, k, code_error;
    k = scanf("%d", &n);

    if (k != 1 || n <= 0)
        code_error = 1;
    else
    {
        prime(n);
        code_error = 0;
    }

    return code_error;
}

void prime(int n)
{
    int i = 2;

    while (i * i <= n)
    {
        while (n % i == 0)
        {
            printf("%d\n", i);
            n = n / i;
        }
        i = i + 1;
    }
    if (n > 1)
        printf("%d", n);
}
