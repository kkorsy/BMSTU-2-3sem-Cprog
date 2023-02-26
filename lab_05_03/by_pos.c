#include "by_pos.h"

int get_size(FILE *f, size_t *size)
{
    int code_return = OK;

    if (fseek(f, 0L, SEEK_END))
        code_return = GET_SIZE_ERROR;
    else
        *size = ftell(f);
        
    fseek(f, 0L, SEEK_SET);
    return code_return;
}

int get_number_by_pos(FILE *f, int pos, int *num)
{
    int code_return = OK;

    fseek(f, pos * sizeof(int), SEEK_SET);
    if (!fread(num, sizeof(int), 1, f))
        code_return = READ_ERROR;

    return code_return;
}

int put_number_by_pos(FILE *f, int pos, int num)
{
    int code_return = OK;

    fseek(f, pos * sizeof(int), SEEK_SET);
    if (!fwrite(&num, sizeof(int), 1, f))
        code_return = WRITE_ERROR;

    return code_return;
}
