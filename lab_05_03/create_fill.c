#include <stdlib.h>
#include "create_fill.h"

int create_file(char *file_name, int num)
{
    int code_return = OK;
    FILE *f = fopen(file_name, "wb");
    if (f == NULL)
        code_return = FILE_OPEN_ERROR;
    else
    {
        code_return = fill_file(f, num);
        fclose(f);
    }

    return code_return;
}

int fill_file(FILE *f, int num)
{
    int x, code_return = OK;

    for (int i = 0; !code_return && i < num; i++)
    {
        x = rand() % 100;
        if (fwrite(&x, sizeof(int), 1, f) != 1)
            code_return = FILL_ERROR;
    }

    return code_return;
}