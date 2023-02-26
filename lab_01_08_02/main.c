#include <stdio.h>
#include <math.h>
#define OK 0
#define ERROR 1
#define MAX 32
void byte_shift(unsigned int a, int n);

int main(void)
{
    unsigned int a;
    int n, code_error, k;

    k = scanf("%u %d", &a, &n);
    
    if (k != 2)
    {
        code_error = ERROR;
        printf("Error: Incorrect types are entered");
    }
    else if (n < 0)
    {
        code_error = ERROR;
        printf("Error: Second argument is negative");
    }
    else
    {
        code_error = OK;
        byte_shift(a, n);
    }

    return code_error;
}

void byte_shift(unsigned int a, int n)
{
    a = (a << n) | (a >> (MAX - n));

    printf("Result: ");
    for (int i = MAX - 1; i >= 0; --i)
        printf("%d", (a >> i) % 2);
}
