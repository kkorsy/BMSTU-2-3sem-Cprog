#include "read_bin_file.h"

int check_bin(FILE *f, int *n)
{
    int k, code_return = OK;
    size_t size;

    if (f == NULL)
        code_return = OPEN_ERROR;
    else if ((code_return = get_size(f, &size)) || size <= 0)
        code_return = GET_SIZE_ERROR;
    else
    {
        k = size / (sizeof(struct student));
        if (size % sizeof(struct student) != 0 || k == 0)
            code_return = NO_DATA;
        else
            *n = k;
    }

    return code_return;
}

int get_size(FILE *f, size_t *size)
{
    int code_return = OK;
    long sz;

    if (fseek(f, 0L, SEEK_END))
        code_return = GET_SIZE_ERROR;
    else
    {
        if ((sz = ftell(f)) < 0)
            code_return = GET_SIZE_ERROR;
        else
        {
            *size = sz;
            if (fseek(f, 0L, SEEK_SET))
                code_return = GET_SIZE_ERROR;
        }
    }

    return code_return;
}

int get_pers_by_pos(FILE *f, int pos, struct student *pers)
{
    int code_return = OK;

    if (fseek(f, pos * sizeof(struct student), SEEK_SET))
        code_return = SEEK_ERROR;
    else if (fread(pers, sizeof(struct student), 1, f) != 1)
        code_return = READ_ERROR;

    return code_return;
}

int put_pers_by_pos(FILE *f, int pos, struct student *pers)
{
    int code_return = OK;

    if (fseek(f, pos * sizeof(struct student), SEEK_SET))
        code_return = SEEK_ERROR;
    else if (fwrite(pers, sizeof(struct student), 1, f) != 1)
        code_return = WRITE_ERROR;

    return code_return;
}
