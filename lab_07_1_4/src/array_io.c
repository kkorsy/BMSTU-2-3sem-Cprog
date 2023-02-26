#include <stdlib.h>
#include "array_io.h"

int array_write(char *file_name, int *pb, int *pe)
{
    int cr = OK;
    FILE *f = fopen(file_name, "w");

    if (!f)
        return OPEN_ERROR;

    cr = print(f, pb, pe);
    fclose(f);
    
    return cr;
}

int print(FILE *f, int *pb, int *pe)
{
    int cr = OK;
    for (int *p = pb; p < pe && !cr; p++)
        if (fprintf(f, "%d ", *p) < 0)
            cr = WRITE_ERROR;
    
    return cr;
}

int array_read(char *file_name, int **arr, size_t *n)
{
    int cr = OK;
    FILE *f = fopen(file_name, "r");
    if (!f)
        return OPEN_ERROR;
    
    cr = elem_count(f, n);
    if (cr == OK)
    {
        *arr = malloc(*n * sizeof(int));
        if (*arr == NULL)
            cr = ALLOC_ERROR;
        else
        {
            rewind(f);
            array_fill(f, *arr, *arr + *n);
        }
    }
    fclose(f);

    return cr;
}

void array_fill(FILE *f, int *pb, int *pe)
{
    for (int *p = pb; p < pe; p++)
        fscanf(f, "%d", p);
}

int elem_count(FILE *f, size_t *n)
{
    int count = 0, temp, cr = OK;

    while (fscanf(f, "%d", &temp) == 1)
        count++;
    
    if (count != 0)
        *n = count;
    else
        cr = DATA_ERROR;
    
    return cr;
}
