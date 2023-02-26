#include "find.h"

int find_elem(int **matrix, size_t n, size_t m, int *elem)
{
    if (n != m)
        return MATRIX_SIZE_ERROR;
    
    int found = 0, max;

    for (size_t i = 1; i < n; i++)
        for (size_t j = i - 1; j < m; j--)
            if (abs(matrix[i][j]) % 10 == 5)
            {
                if (!found || (found && matrix[i][j] > max))
                    max = matrix[i][j];
                found = 1;
            }
    if (!found)
        return NOT_FOUND_ERROR;
    *elem = max;

    return OK;
}
