#include "task.h"

int process(FILE *f, int *m1, int *m2)
{
    int x, y, code_return = OK;
    int max_1, max_2;
    
    if (fscanf(f, "%d%d", &x, &y) != 2)
        code_return = NO_DATA;
    else
    {
        if (x >= y)
        {
            max_1 = x;
            max_2 = y;
        }
        else
        {
            max_1 = y;
            max_2 = x;
        }

        while (fscanf(f, "%d", &x) == 1)
        {
            if (x >= max_1)
            {
                max_2 = max_1;
                max_1 = x;
            }
            else if (x >= max_2)
                max_2 = x;
        }
        *m1 = max_1;
        *m2 = max_2;
    }

    return code_return;
}
