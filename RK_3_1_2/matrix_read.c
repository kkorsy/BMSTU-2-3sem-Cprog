#include "matrix_read.h"

int matrix_create(FILE *f, int ***matrix, size_t *n, size_t *m)
{
    int t, cr = OK;

    if (fscanf(f, "%zu%zu", n, m) != 2)
        return READ_ERROR;

    int **temp = calloc(*n, sizeof(int *));
    if (temp == NULL)
            return ALLOC_ERROR;

    for (size_t i = 0; i < *n; i++)
    {
        temp[i] = malloc(*m * sizeof(int));
        if (temp[i] == NULL)
        {
            matrix_free(temp, *n);
            return ALLOC_ERROR;
        }
    }


    for (size_t i = 0; i < *n && !cr; i++)
        for (size_t j = 0; j < *m && !cr; j++)
        {
            if (fscanf(f, "%d", &t) != 1)
                cr = READ_ERROR;
            else
                temp[i][j] = t;
        }

    if (cr == OK)
        *matrix = temp;
    else
        matrix_free(temp, *n);

    return cr;
}

void matrix_free(int **matrix, size_t n)
{
    for (size_t i = 0; i < n; i++)
        free(matrix[i]);
    free(matrix);
}
