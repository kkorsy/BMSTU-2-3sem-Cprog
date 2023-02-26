#include "matrix_alloc.h"

/*
void matrix_free(double **data, size_t n)
{
    (void) n;
    free(data);
}

double **matrix_alloc(size_t n, size_t m)
{
    double **data = malloc(n * sizeof(double *) + n * m * sizeof(double));
    if (!data)
        return NULL;

    for (size_t i = 0; i < n; i++)
        data[i] = (double *)((char *) data + n * sizeof(double *) + i * m * sizeof(double));
    
    return data;
}
*/

void matrix_free(double **data, size_t n)
{
    for (size_t i = 0; i < n; i++)
        free(data[i]);
    free(data);
}

double **matrix_alloc(size_t n, size_t m)
{
    double **data = malloc(n * sizeof(double *));
    if (!data)
        return NULL;

    for (size_t i = 0; i < n; i++)
    {
        data[i] = malloc(m * sizeof(double));
        if (!data[i])
        {
            matrix_free(data, i);
            return NULL;
        }
    }

    return data;
}
