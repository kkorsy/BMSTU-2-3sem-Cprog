#ifndef MATRIX_READ_H
#define MATRIX_READ_H

#include <stdio.h>
#include <stdlib.h>
#include "errors.h"

int matrix_create(FILE *f, int ***matrix, size_t *n, size_t *m);
void matrix_free(int **matrix, size_t n);

#endif // MATRIX_READ_H
