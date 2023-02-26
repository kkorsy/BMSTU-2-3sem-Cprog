#include "task.h"

int main(void)
{
    int code_return, m1, m2;
    FILE *f = stdin;

    code_return = process(f, &m1, &m2);
    if (!code_return)
        printf("%d %d\n", m1, m2);

    return code_return;
}