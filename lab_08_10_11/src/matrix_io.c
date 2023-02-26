#include "matrix_io.h"
#include "matrix_alloc.h"

int matrix_read(FILE *f, double **data, size_t n, size_t m)
{
    double tmp;
    for (size_t i = 0; i < n; i++)
        for (size_t j = 0; j < m; j++)
        {
            if (fscanf(f, "%lf", &tmp) == 1)
                data[i][j] = tmp;
            else
                return READ_ERROR;
        }
    if (!feof(f) && fscanf(f, "%lf", &tmp) == 1)
        return MORE_DATA_ERROR;

    return OK;
}

int matrix_create(char *filename, double ***data, size_t *n, size_t *m)
{
    int rc = OK;

    FILE *f = fopen(filename, "r");
    if (f == NULL)
        return OPEN_ERROR;
    
    if (fscanf(f, "%zu%zu", n, m) != 2 || *n == 0 || *m == 0)
        rc = READ_ERROR;
    else
    {
        *data = matrix_alloc(*n, *m);
        if (!data)
            rc = ALLOC_ERROR;
        else 
        {
            rc = matrix_read(f, *data, *n, *m);
            if (rc != OK)
                matrix_free(*data, *n);
        }
    }
    fclose(f);

    return rc;
}

int matrix_print(char *filename, double **data, size_t n, size_t m)
{
    FILE *f = fopen(filename, "w");
    if (f == NULL)
        return OPEN_ERROR;

    fprintf(f, "%zu %zu\n", n, m);
    
    for (size_t i = 0; i < n; i++)
    {
        for (size_t j = 0; j < m; j++)
            fprintf(f, "%lf ", data[i][j]);
        fprintf(f, "\n");
    }
    fclose(f);

    return OK;
}
