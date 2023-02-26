#include <stdio.h>
#include "sort.h"

int sort(char *file_name)
{
    int temp, x, code_return = OK;
    size_t s;
    FILE *f = fopen(file_name, "rb+");
    
    if (f == NULL)
        code_return = FILE_OPEN_ERROR;
    else
    {
        get_size(f, &s);
        if (s <= 0 || (s % sizeof(int)) != 0)
            code_return = GET_SIZE_ERROR;
        else
        {
            for (size_t i = 1; i < s / sizeof(int); i++)
            {
                get_number_by_pos(f, i, &temp);
                for (int j = i - 1; j >= 0; j--)
                {   
                    get_number_by_pos(f, j, &x);
                    if (x < temp)
                        break;
                    
                    put_number_by_pos(f, j + 1, x);
                    put_number_by_pos(f, j, temp);
                }
            }
        }
        fclose(f);
    }

    return code_return;
}
