#include "errors.h"
#include "find.h"
#include "matrix_read.h"

int main(int argc, char **argv)
{
    int cr = OK;
    int **matrix, elem;
    size_t n, m;

    if (argc != 2)
            return ARGS_ERROR;

    FILE *f = fopen(argv[1], "r");
    if (f == NULL)
            return OPEN_ERROR;

    cr = matrix_create(f, &matrix, &n, &m);
    if (cr == OK)
    {
        cr = find_elem(matrix, n, m, &elem);
        if (cr == OK)
            printf("%d\n", elem);
        matrix_free(matrix, n);
    }

    fclose(f);
    return cr;
}
