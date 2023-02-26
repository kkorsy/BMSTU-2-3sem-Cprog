#include <stdio.h>
#include "print_file.h"

int print(char *file_name)
{
    int code_return = OK;
    FILE *f = fopen(file_name, "rb");

    if (f == NULL)
        code_return = FILE_OPEN_ERROR;
    else
    {
        int num;
        size_t size;
        get_size(f, &size);
        if (size <= 0 || (size % sizeof(int)) != 0)
            code_return = GET_SIZE_ERROR;
        else
            for (size_t i = 0; !code_return && i < size / sizeof(int); i++)
            {
                if (fread(&num, sizeof(int), 1, f) != 1)
                    code_return = READ_ERROR;
                else
                    printf("%d ", num);
            }

        fclose(f);
    }

    return code_return;
}
